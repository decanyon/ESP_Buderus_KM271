let ws;
let heartbeatTimeout;
const maxReconnectDelay = 5000;
const minReconnectDelay = 1000;
let reconnectDelay = minReconnectDelay;

function setupWS() {
  ws = new WebSocket("ws://" + window.location.host + "/ws");

  ws.onopen = function () {
    console.log("WebSocket connected");
    resetHeartbeat();
    hideReloadBar();
    reconnectDelay = minReconnectDelay;
  };

  ws.onclose = function () {
    console.log("WebSocket disconnected. Retrying...");
    attemptReconnect();
    showReloadBar();
  };

  ws.onmessage = function (event) {
    let message = JSON.parse(event.data);
    //console.log(message);
    if (message.type === "redirect") {
      console.log("Redirecting to:", message.url);
      ws.close();
      window.location.href = message.url;
    } else if (message.type === "heartbeat") {
      resetHeartbeat();
    } else if (message.type === "updateText") {
      updateText(message);
    } else if (message.type === "setLanguage") {
      setLanguage(message);
    } else if (message.type === "updateJSON") {
      updateJSON(message);
    } else if (message.type === "updateValue") {
      updateValue(message);
    } else if (message.type === "updateState") {
      updateState(message);
    } else if (message.type === "updateSetIcon") {
      updateSetIcon(message);
    } else if (message.type === "hideElement") {
      hideElement(message);
    } else if (message.type === "updateHref") {
      updateHref(message);
    } else if (message.type === "updateBusy") {
      updateBusy(message);
    } else if (message.type === "showElementClass") {
      showElementClass(message);
    } else if (message.type === "logger") {
      logger(message);
    } else if (message.type === "cmdLogClr") {
      cmdLogClr(message);
    } else if (message.type === "otaProgress") {
      otaProgress(message);
    } else if (message.type === "updateDialog") {
      updateDialog(message);
    }
  };
}

// Heartbeat-Timeout zurücksetzen
function resetHeartbeat() {
  clearTimeout(heartbeatTimeout);
  heartbeatTimeout = setTimeout(() => {
    console.warn("No heartbeat received, reconnecting...");
    ws.close();
    showReloadBar();
  }, 5000);
}

function attemptReconnect() {
  setTimeout(() => {
    console.log(`Attempting reconnect in ${reconnectDelay / 1000} seconds...`);
    setupWS();
    reconnectDelay = Math.min(reconnectDelay * 2, maxReconnectDelay);
  }, reconnectDelay);
}

function sendData(elementId, value) {
  if (ws.readyState === WebSocket.OPEN) {
    const message = {
      type: "sendData",
      elementId: elementId,
      value: String(value),
    };
    ws.send(JSON.stringify(message));
  } else {
    console.error("WebSocket is not open. Cannot send data.");
  }
}

function updateText(data) {
  var element = document.getElementById(data.id);
  //console.log(element);
  if (element) {
    if (data.isInput) {
      element.value = data.text;
    } else {
      element.innerHTML = data.text;
    }
  }
}

function setLanguage(data) {
  console.log("Set language to:", data.language);
  localizePage(data.language);
}

function updateJSON(data) {
  Object.keys(data).forEach(function (key) {
    if (key != "type") {
      // skip the first key
      let [elementID, typSuffix] = key.split("#");
      let element = document.getElementById(elementID);
      if (!element) {
        console.error("unknown element:", key);
        return;
      }
      let value = data[key];
      switch (typSuffix) {
        case "v": // value
          element.value = value;
          break;
        case "c": // checked
          element.checked = value === "true";
          toggleElementVisibility(
            element.getAttribute("hideOpt"),
            element.checked
          );
          break;
        case "l": // Label = innerHTML
          element.innerHTML = value;
          break;
        case "i": // icon
          element.className = "svg " + value;
          break;
        default:
          console.error("unknown typ:", typSuffix);
      }
    }
  });
}

function updateValue(data) {
  var element = document.getElementById(data.id);
  if (element) {
    if (data.isInput) {
      element.value = data.value;
    }
  }
}

// update switch elements
function updateState(data) {
  var element = document.getElementById(data.id);
  if (element && (element.type === "checkbox" || element.type === "radio")) {
    element.checked = data.state;
    toggleElementVisibility(element.getAttribute("hideOpt"), element.checked);
  }
}

// update add class to element
function updateSetIcon(data) {
  var element = document.getElementById(data.id);
  if (element) {
    element.className = "svg " + data.icon;
  }
}

// hide/show element
function hideElement(data) {
  var element = document.getElementById(data.id);
  if (element) {
    element.style.display = data.hide ? "none" : "";
  }
}

// update href
function updateHref(data) {
  var element = document.getElementById(data.id);
  if (element) {
    element.href = data.href;
  }
}

// update Busy
function updateBusy(data) {
  var element = document.getElementById(data.id);
  if (element) {
    element.setAttribute("aria-busy", data.busy);
  }
}

// hide/show elements based on className
function showElementClass(data) {
  const elements = document.querySelectorAll(`.${data.className}`);
  elements.forEach((element) => {
    element.style.display = data.show ? "inline-flex" : "none";
  });
}

// add log message
function logger(data) {
  var logOutput = document.getElementById("p10_log_output");
  if (data.cmd === "add_log") {
    logOutput.innerHTML += data.entry + "<br>";
  } else if (data.cmd === "clr_log") {
    logOutput.innerHTML = "";
  }
}

// update ota-progress bar
function otaProgress(data) {
  var progress = data.progress;
  document.getElementById("ota_progress_bar").value = progress;
  document.getElementById(
    "ota_status_txt"
  ).textContent = `Update Progress: ${progress}%`;
}

// close update dialog
function updateDialog(data) {
  var dialog = document.getElementById(data.id);
  if (data.state == "open") {
    dialog.showModal();
  } else if (data.state == "close") {
    dialog.close();
  }
}

// Function for switching the visibility of elements
function toggleElementVisibility(className, isVisible) {
  const elements = document.querySelectorAll(`.${className}`);
  elements.forEach((element) => {
    element.style.display = isVisible ? "" : "none";
  });
}

// Function for initializing the visibility based on the status of the switches
function initializeVisibilityBasedOnSwitches() {
  document
    .querySelectorAll('input[type="checkbox"][role="switch"]')
    .forEach(function (switchElement) {
      // Evaluate the status of the switch and adjust visibility
      toggleElementVisibility(
        switchElement.getAttribute("hideOpt"),
        switchElement.checked
      );
    });
}

// OTA: function is called when the ota-file is selected
function ota_sub_fun(obj) {
  var a = obj.value;
  console.log(a);
  var fileName = a.replace(/^.*[\\\/]/, "");
  console.log(fileName);
  document.getElementById("ota_file_input").textContent = fileName;
  document.getElementById("ota_update_btn").disabled = false;
  document.getElementById("ota_progress_bar").style.display = "block";
  document.getElementById("ota_status_txt").style.display = "block";
}

// CONFIG-FORM: function for download config.json file
function exportConfig() {
  var a = document.createElement("a");
  a.href = "/config-download";
  a.download = "";
  document.body.appendChild(a);
  a.click();
  document.body.removeChild(a);
}

// CONFIG-FORM: function to activate import button and show status
function file_sub_fun(obj) {
  document.getElementById("file_upload_btn").disabled = false;
  document.getElementById("upload_status_txt").style.display = "block";
}

// validation for date and time inputs
const dateInput = document.getElementById("p12_dti_date");
const timeInput = document.getElementById("p12_dti_time");
const submitButton = document.getElementById("p12_dti_btn");
function validateInputs() {
  const isDateValid = dateInput.value !== "";
  const isTimeValid = timeInput.value !== "";
  dateInput.setAttribute("aria-invalid", !isDateValid);
  timeInput.setAttribute("aria-invalid", !isTimeValid);
  submitButton.disabled = !(isDateValid && isTimeValid);
}
dateInput.addEventListener("input", validateInputs);
timeInput.addEventListener("input", validateInputs);

// localization of web texts
function localizePage(lang = "en") {
  document.querySelectorAll("[data-i18n]").forEach((elem) => {
    const i18nValue = elem.getAttribute("data-i18n");
    const [translationPart, addon] = i18nValue.split("++", 2);
    const matches = translationPart.split(/(\$.+?\$)/).filter(Boolean);
    let text = "";

    for (const match of matches) {
      if (match.startsWith("$") && match.endsWith("$")) {
        text += match.slice(1, -1);
      } else {
        // check if translation key is valid
        if (translations.hasOwnProperty(match)) {
          text += translations[match][lang] || match;
        } else {
          console.error(`translation key "${match}" not found`);
          continue;
        }
      }
    }
    if (addon) {
      text += addon;
    }
    elem.innerText = text;
  });
}

// to show reload bar if connection is lost
function showReloadBar() {
  document.getElementById("connectionLostBar").style.display = "flex";
}

// to hide reload bar if connection is lost
function hideReloadBar() {
  document.getElementById("connectionLostBar").style.display = "none";
}

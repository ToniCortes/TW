module.exports = [
  {
    "type": "heading",
    "defaultValue": "TypeWriter Configuration"
  },
  {
    "type": "text",
    "defaultValue": "Hope this helps you get the best of this whatchface."
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Colors"
      },
      {
        "type": "color",
        "messageKey": "BackGroundColor",
        "defaultValue": "0xFFFFFF",
        "label": "Background Color"
      },
      {
        "type": "color",
        "messageKey": "TextColor",
        "defaultValue": "0x000000",
        "label": "Text Color"
      },
      {
        "type": "select",
        "messageKey": "Language",
        "defaultValue": "Catalan",
        "label": "Language",
        "options": [
          { 
            "label": "Català",
            "value": "C"
          },
          { 
            "label": "Español",
            "value": "S"
          },
           { 
            "label": "English",
            "value": "E"
          }
        ]
      }
    ]
  },
  
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "More Settings"
      },
      {
        "type": "toggle",
        "messageKey": "BlueTooth",
        "label": "Notify BT disconnection",
        "defaultValue": true
      },
      {
        "type": "toggle",
        "messageKey": "ShowDate",
        "label": "Show date",
        "defaultValue": true
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
];
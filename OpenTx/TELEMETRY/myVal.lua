-- ========================================================================================
--      Meine Welt in meinem Kopf
-- ========================================================================================
-- Projekt:       Sensor Daten über Smart Port versenden mit dem Arduino
-- Author:        Johannes P. Langner
-- Controller:    Arduino UNO / Mini
-- Transceiver:   FrSky XLite Pro 
-- Description:   Der Empfangene Sensor Wert wird in den entsprechenden Temperatur Wert
--				  umgerechnet. Der Script kann am Ende über das Display eingebunden werden.
-- Stand:         11.09.2021
-- ========================================================================================

-- Init function
local function init_func()
	-- init_func is called once when model is loaded
	return 0
end

local function bg_func()
  -- bg_func is called periodically (always, the screen visibility does not matter)
  return 0
end

-- main methode it iterated 
local function run_func(event)
	lcd.clear()
	
	local receivedValue = getValue('TEMP')
	local toDecValue = receivedValue * 0.0625;
	lcd.drawText(10, 10, "Temperature", MIDSIZE)
	lcd.drawText(10, 25, string.format("%.2f", toDecValue), MIDSIZE)
	
	return 0
end

return { run=run_func, background=bg_func, init=init_func  }
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
	
	local receivedValue = getValue('5900')
	lcd.drawRectangle(10, 10, receivedValue, 5, SOLID)
	
	local toDecValue = receivedValue / 100.0
	lcd.drawText(10, 20, string.format("%.2f", toDecValue), MIDSIZE)
	
	
	return 0
end

return { run=run_func, background=bg_func, init=init_func  }
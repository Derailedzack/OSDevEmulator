_G.MemoryMap = {}
function MemoryMap.Init()
    MemoryMap.Devices = {}
    return MemoryMap
end
function MemoryMap.AddDevice(device)
    if MemoryMap.Devices[device.name] ~= nil then 
        print("Device" .. device.name .. "Already exists!")
        return
    end
    MemoryMap.Devices[device.name] = device
end
function MemoryMap.WriteToDevice(device,offset,val)
    local dev_device = MemoryMap.Devices[device.name]
    if dev_device.write ~= nil then
        dev_device.write(offset,val)
    end
end
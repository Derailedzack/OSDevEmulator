--MemoryMap.Devices = {}
require("MemoryMap")
function DumpTable(table_,table_name)
    
    for key,val in pairs(table_) do 
        print(table_name .."[" .. key .. "]" .. "=" .. tostring(val)) 
        end
end
--local test = {}
--test.name = "Test"
local function Test()
  
   --MemoryMap.Init()
   --MemoryMap.AddDevice(test,test.name)
   --DumpTable(MemoryMap.Devices,"MemoryMap.Devices")
  -- print(tostring(MemoryMap.Devices))
end

Test()
--print(MemoryMap_lib)
--print(tes(DumpTable))

--DumpTable(MemoryMap.Devices,"MemoryMap.Devices")
from bleak import BleakScanner
import asyncio

address = {
    1: "00:22:09:01:F8:C5",
    2: "00:22:09:01:FE:87",
    3: "00:22:09:01:FD:57",
}

async def search():
    async with BleakScanner() as scanner:
        await asyncio.sleep(5.0)
        devices = scanner.discovered_devices
        
    # 리스트 출력
    for d in devices:
        print(d)
        

loop = asyncio.get_event_loop()
loop.run_until_complete(search())
loop.close()
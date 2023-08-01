from bleak import BleakScanner
import asyncio

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
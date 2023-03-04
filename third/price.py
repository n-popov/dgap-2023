import requests
import json

print(json.dumps(requests.get('https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT').json()), file=open('price.json', 'w'))

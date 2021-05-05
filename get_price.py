from coinbase.wallet.client import Client
import time

client = Client('NTkXQa54Zgry1bcl', 'gj1x6XnWEsX7T6nKmlfyD9Cg0jGOSiI3', api_version='2020-12-06')

currency_code = 'INR'  # can also use EUR, CAD, etc.

#print ('Current bitcoin price in %s: %s' % (currency_code, price.amount))

while(True):
    price = client.get_spot_price(currency=currency_code)
    t = client.get_time()

    with open('price.txt', 'a') as f:
        f.write('\n')
        f.write(t['iso'])
        f.write("@")
        f.write(price.amount)

    time.sleep(3)

import hashlib

# Data to be hashed
beforehash = "HeyImASimplePOWAlgo"
nonce = 0 

result = hashlib.sha1(beforehash.encode())

# Just print the current hash
print(result.hexdigest())

while True:
    # Slowly increase the nonce
    nonce += 1
    # pow before hash, it just adds the "!"
    powbh = beforehash + "!"

    # This is pow in a nutshell. Just increase a number till you reach a "target"
    pow = powbh + str(nonce)

    hashpow = hashlib.sha1(pow.encode())
    hashpowstr = hashpow.hexdigest()
    target = hashpowstr[0:4]

    print("Nonce: " + str(nonce))
    print("Hash: " + hashpowstr)

    if target == '0000':
        break

print("Found satisfying hash with nonce " + str(nonce))

# you need to install the cryptography package in order to run this
# pip install cryptography
from cryptography.fernet import Fernet

# encrypt text using a key
def my_encrypt(key, text):
    f = Fernet(key)
    t = f.encrypt(text)
    return t

# decrypt text using a key
def my_decrypt(key, text):
    f = Fernet(key)
    t = f.decrypt(text)
    return t

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    my_text = b'0.0, 0.0, 21.6, 56'
    print(f'Text to encrypt: {my_text}\n')
    key = Fernet.generate_key()
    my_encrypted_text = my_encrypt(key, my_text)
    print(f'Encrypted text: {my_encrypted_text}\n')
    my_decrypted_text = my_decrypt(key, my_encrypted_text)
    print(f'Decrypted tex: {my_decrypted_text}\n')
    key_type = type(key)
    print(f'TypeOf Key: {key_type}')


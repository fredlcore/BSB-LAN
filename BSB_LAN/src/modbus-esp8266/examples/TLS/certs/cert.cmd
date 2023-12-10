set OPATH=C:\Program Files\OpenSSL-Win64\bin

rem CA
"%OPATH%\openssl" genrsa -out ca_key.pem 2048
"%OPATH%\openssl" req -x509 -new -nodes -key ca_key.pem -days 4096 -config ca.conf -out ca_cer.pem

rem SERVER
"%OPATH%\openssl" genrsa -out server_key.pem 2048
"%OPATH%\openssl" req -out server_req.csr -key server_key.pem -new -config server.conf
"%OPATH%\openssl" x509 -req -in server_req.csr -out server_cer.pem -sha256 -CAcreateserial -days 4000 -CA ca_cer.pem -CAkey ca_key.pem
"%OPATH%\openssl" rsa -in server_key.pem -pubout -out server_pubkey.pem

rem CLIENT
"%OPATH%\openssl" genrsa -out client1_key.pem 2048
"%OPATH%\openssl" req -out client1_req.csr -key client1_key.pem -new -config client.conf
"%OPATH%\openssl" x509 -req -in client1_req.csr -out client1_cer.pem -sha256 -CAcreateserial -days 4000 -CA ca_cer.pem -CAkey ca_key.pem


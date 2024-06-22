# IoT Project: Realtime Temperature and Humidity Monitoring

## Deskripsi Proyek

Proyek ini adalah sistem monitoring suhu dan kelembaban secara real-time menggunakan NodeMCU ESP8266 dan sensor DHT11. Data yang diperoleh dari sensor ditampilkan di layar LCD dan dikirimkan ke server MQTT setiap 2 detik. Pengguna juga dapat mengontrol LED yang terhubung ke NodeMCU melalui antarmuka web.

## Fitur

### Monitoring Suhu dan Kelembaban
1. Menggunakan sensor DHT11 untuk membaca suhu dan kelembaban.
2. Menampilkan hasil pembacaan pada LCD.
3. Mengirimkan data ke server MQTT setiap 2 detik.

### Kontrol LED
1. Terdapat 3 LED yang terhubung ke pin D5, D6, dan D7.
2. LED dapat dinyalakan dan dimatikan melalui antarmuka web.

### Antarmuka Web
1. Menampilkan grafik suhu dan kelembaban secara real-time.
2. Menyediakan tombol untuk mengontrol LED.
3. Menggunakan WebSocket untuk komunikasi real-time dengan server Node.js.


## Instalasi dan Penggunaan

### Persiapan Hardware
1. NodeMCU ESP8266
2. Sensor DHT11
3. LCD Display 2x16+I2C Modu
4. 2 Breadboard
5. 3 LED 
6. Kabel USB
7. Kabel jumper male to male dan male to female

### Persiapan Software

1. Install Laravel:
    ```sh
    composer create-project laravel/laravel iotMonitoring
   
    cd /iotMonitoring
    ```
2. Instal Laravel Breeze
    ```sh
   composer require laravel/breeze --dev
   
   php artisan breeze: install
    ```
   
   Konfigurasi file .env untuk setup database.

    ```sh
   php artisan migrate
   npm install
   npm run dev
    ```
3. Jalankan server web:

    ```sh
   php artisan serve
    ```

3. Jalankan server WebSocket:

    ```sh
   npm run iot
    ```
   

Link video YouTube : https://www.youtube.com/watch?v=fF1s-79jZDo

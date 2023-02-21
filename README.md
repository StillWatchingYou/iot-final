# iot-final

Trong qua trình học môn IoT, chúng tôi đã tạo ra 1 dự án với mô hình như sau:

2 node điều khiển với cấu hình là:
  - node 1 (phòng ngủ):
    + 1 Vi xử lý ESP32
    + 1 cảm biến nhiệt độ DHT11
    + 1 led 
    + và 1 số điện trở
  - node 2 (phòng khách):
    + 1 Vi xử lý ESP32
    + 1 quang trở
    + 1 quạt
    + và 1 số điện trở

Quy trình xử lý: 
- 2 node cảm biến này thực hiện truyền dữ liệu tới Broker Node-red bằng giao thức MQTT

- Broker này sẽ truyển dữ liệu tới Firebase bằng giao thức http

- Firebase sẽ chịu trách nhiệm lưu trữ và cập nhật dữ liệu theo thời gian

- Chúng tôi tạo ra 1 giao diện để các bạn có thể dễ dàng theo dõi các thông tin và điều khiển các thiết bị tại địa chỉ: "https://stillwatchingyou.github.io/". Giao diện này lấy dữ liệu từ Firebase. Đây là giao diện online hoàn toàn

- Ngoài ra node-red cũng hộ trợ chúng tôi tạo ra 1 giao diện để theo dõi và điều khiển local

Về ESP32: 

Trong file github này chúng tôi cung cấp file lập trình cho cặp vi xử lý ESP32(iot-livingroom/scr/main.cpp và iot-bedroom/scr/main.cpp) Bằng cách setup hệ thống với mô hình phù hợp như trên. Người dùng tiến hành thay đổi 1 vài thông tin như ssid,password của Wifi, Địa chỉ IP sau đó tải code vào ESP32 là hoàn thành việc setup node cảm biển

Về Node-red:

Các bạn có thể tìm hiểu về node-red tại đây: https://nodered.org/
Các bạn setup như hình "setup-nodered1.png" và "setup-nodered2.png" tôi có đính kèm bên dưới

Về Firebase:

Các bạn có thể tìm hiểu tại đây: "https://firebase.google.com/", 
"https://wiki.matbao.net/firebase-la-gi-giai-phap-lap-trinh-khong-can-backend-tu-google/"

Setup API key phù hợp để thực hiện dự án giống như của chúng tôi



Chúc các bạn thành công.
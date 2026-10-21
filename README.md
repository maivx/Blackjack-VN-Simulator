# 🃏 Mô Phỏng & Phân Tích Chiến Lược Xì Dách Dân Gian (OOP C++ & Python)

Dự án lập trình hướng đối tượng (OOP) mô phỏng trò chơi bài **Xì Dách (Blackjack Việt Nam)** kết hợp phân tích xác suất qua hàng chục nghìn ván đấu tự động. Dự án số hóa các quy luật dân gian phức tạp, xây dựng các chiến lược người chơi/nhà cái bằng OOP và tích hợp Python (`matplotlib`) để trực quan hóa dữ liệu tài sản.

---

## ✨ Điểm Nhấn Thuật Toán & Luật Chơi Dân Gian

* **Hệ thống lá Át (A) linh hoạt thông minh:**
  * **$\le 3$ lá:** Lá Át có thể linh hoạt tính là $11$, $10$ hoặc $1$ tùy tình huống.
  * **$> 3$ lá:** Lá Át tự động tính cố định là $1$ điểm.
  * **Quy tắc đặc biệt:** Nếu tổng điểm đạt **22** với đúng **3 lá bài**, hệ thống tự động quy đổi về **21 điểm** để cứu người chơi khỏi bị Quắc (Bust).
* **Các bộ bài đặc biệt (Ưu tiên từ cao xuống thấp):**
  * **Xì Bàng:** 2 lá Át (Thắng tuyệt đối).
  * **Xì Dách:** 1 lá Át kết hợp với 10, J, Q hoặc K.
  * **Ngũ Linh:** Rút đủ 5 lá bài mà tổng điểm $\le 21$.

---

## 👥 Mô Hình Hóa Chiến Lược Người Chơi (Inheritance trong OOP)

Dự án ứng dụng tính kế thừa (`Inheritance`) và ghi đè phương thức (`override`) trong OOP để chia người chơi thành 3 hình mẫu hành vi.

## 🧠 Mô Hình Hóa Chiến Lược Người Chơi (Inheritance trong OOP)

Dự án ứng dụng tính kế thừa (`Inheritance`) và ghi đè phương thức (`override`) trong Lập trình Hướng đối tượng (OOP) để phân tách các hình mẫu hành vi chiến thuật khác nhau của người chơi trong trò chơi Blackjack.

### 1. Người chơi Nhát gan / An toàn (`FunkyPlayer`)
* **Hành vi (Code Logic):** Hàm `MakeDecision` được ghi đè để ưu tiên rút thêm bài (`Hit`) nếu điểm số dưới 16. Ngay khi đạt mức $\ge 16$ điểm (ngưỡng "đủ tuổi" tối thiểu) hoặc khi đã cầm đủ 5 lá bài, người chơi này lập tức dừng rút (`Stand`).
* **Mục tiêu:** Tránh rủi ro bị Quắc (`Bust`) ở mức tối đa bằng cách dừng lại ngay ở ranh giới an toàn nhất, kỳ vọng nhà cái sẽ tự Quắc hoặc có điểm thấp hơn.

### 2. Người chơi Tối ưu (`OptimalPlayer`)
* **Hành vi (Code Logic):** Tiếp tục rút thêm bài (`Hit`) nếu điểm số dưới 17, chấp nhận rủi ro ở mốc 16 điểm vốn dễ bị nhà cái bắt bài. Chỉ dừng lại (`Stand`) khi đạt từ $\ge 17$ điểm trở lên hoặc khi đã có đủ 5 lá bài.
* **Mục tiêu:** Nâng cao ngưỡng an toàn, tạo ra một thế bài vững chắc hơn và cân bằng tốt giữa rủi ro rút lố với tỷ lệ thắng thực tế trước nhà cái.

### 3. Người chơi Máu liều (`RecklessPlayer`)
* **Hành vi (Code Logic):** Đây là class có logic phức tạp và rủi ro cao nhất:
  * Rút bài (`Hit`) liên tục nếu tổng điểm dưới 18.
  * **Trường hợp đặc biệt:** Nếu đang có đúng 18 điểm và đã cầm 4 lá bài, người chơi vẫn tiếp tục rút lá thứ 5 để săn Ngũ Linh (bất chấp rủi ro Quắc cực cao). Nếu tổng điểm vượt ngưỡng $\ge 28$, hệ thống sẽ kích hoạt cờ kiểm tra `checkBetter28 = true`.
  * Chỉ dừng lại (`Stand`) khi đạt từ 18 điểm trở lên.
* **Mục tiêu:** Bỏ qua sự an toàn để theo đuổi điểm số tuyệt đối (19–21 điểm) hoặc mù quáng săn Ngũ Linh khi đã cầm 4 lá trên tay.


## 🏦 Giải Mã Lợi Thế Nhà Cái (Dealer Strategy)

Thuật toán của Nhà cái được tối ưu hóa nhằm tối đa hóa lợi nhuận và quản trị rủi ro.
* **Giai đoạn 1 (Quét tuyệt đối):** Kiểm tra `SpecialWin()` ngay từ 2 lá đầu để thu hồi tiền từ Xì Bàng/Xì Dách.
* **Giai đoạn 2 (Xét bài sớm lúc 15 điểm):** Khi đạt $\ge 15$ điểm, Dealer tạm dừng rút để "thu họ" nhóm người chơi cầm 3-4 lá (nhóm có tỷ lệ Quắc cao nhất) trước khi mạo hiểm bốc thêm cho chính mình.
* **Giai đoạn 3 (Ngưỡng an toàn 17 điểm):** Bắt buộc rút tiếp nếu dưới 17 điểm để gây sức ép tối đa lên những người chơi dằn non.

---

## 📊 Thống Kê Xác Suất & Tỷ Lệ Quắc (Bust Rate)

Chương trình cung cấp bảng kết toán tài sản sau mô phỏng kèm theo **Bảng thống kê tỷ lệ Quắc** và **Tỷ lệ thắng của nhà cái từ 16 - 20 điểm**, giúp chứng minh các luận điểm khoa học trong báo cáo.
* Chứng minh người chơi *Reckless* có tỷ lệ Quắc cao vượt trội.
* Chứng minh lợi thế toán học và tỷ lệ thắng thực tế của Nhà cái khi dừng bài ở các mốc điểm khác nhau.

---

## 📂 Cấu Trúc Mã Nguồn (Multi-file OOP Architecture)

* `Card.h` / `Card.cpp`: Quản lý cấu trúc lá bài, khởi tạo bộ bài và thuật toán xáo trộn `std::shuffle`.
* `Hand.h` / `Hand.cpp`: Xử lý logic tính điểm, kiểm tra Át linh hoạt, Xì Bàng, Xì Dách, Ngũ Linh và Quắc.
* `Player.h` / `Player.cpp`: Định nghĩa lớp trừu tượng `Player` và các lớp con chiến lược (`FunkyPlayer`, `OptimalPlayer`, `RecklessPlayer`).
* `Dealer.h` / `Dealer.cpp`: Đóng gói hành vi thông minh và quỹ tiền của Nhà cái.
* `main.cpp`: Điều phối vòng lặp mô phỏng, xuất bảng kết toán tài sản, thống kê tỷ lệ Quắc và sinh script Python.
* `bieu_do.py`: Script tự động trực quan hóa biến động dòng tiền bằng `matplotlib`.

---

## Hướng dẫn cài đặt và chạy chương trình

### 1. Yêu cầu hệ thống
* Trình biên dịch C++ hỗ trợ C++17 trở lên (ví dụ: `g++`).
* Python 3.x (để vẽ biểu đồ dòng tiền).

### 2. Cài đặt thư viện Python
Chạy lệnh sau trong terminal để cài đặt thư viện đồ họa cần thiết:
```bash
pip install matplotlib
```
### 3. Biên dịch project C++
Sử dụng trình biên dịch `g++` để liên kết các file nguồn và tạo file chạy
```bash
g++ -std=c++17 main.cpp Card.cpp Hand.cpp Player.cpp Dealer.cpp -o main
```
### 4. Chạy mô phỏng
Thực thi file vừa biên dịch và nhập số lượng ván chơi (ví dụ: '100000' ván để khử đi yếu tố may rủi)
* Trên Windows
```DOS
.\main
```
* Trên macOS/Linux
```bash
./main
```
### 5. Xem biểu đồ thống kê 
Sau khi chương trình C++ chạy xong và sinh ra dữ liệu, chạy file Python (bieu_do.py) để xem biểu đồ thống kê dòng tiền
```bash
python bieu_do.py
```




# Game2D Development with NinjaGaidenNES

Đầy là Project cuối kì bộ môn __Nhập môn phát triển game__ 

Thuộc giáo trình Khoa __Công Nghệ Phần Mềm__ của __ĐẠI HỌC CÔNG NGHỆ THÔNG TIN - ĐHQG-TPHCM__ 

## Giới thiệu

Được lập trình trên nền tảng __DirectX9__. Mô phỏng tại tựa game __Ninja Gaiden NES__ từ Stage 3.1 đến Stage 3.3

Repo chứa đồ án cuối kỳ của nhóm sinh viên năm 2 bao gồm sự đóng góp của:

* _Nguyễn Tiến Đạt: nguyentiendat150699@gmail.com_
* Và những người khác không muốn đề tên

Đồ án được thiết kế tối ưu nhất mà nhóm có thể, nhằm tạo ra Framework cho môn học.
Repo GitHub này được public nhằm cung cấp cho sinh viên nào có nhu cầu hoặc cần sử dụng trong quá trình học tập nghiên cứu.

*__Hy vọng mọi người cảm thấy hài lòng với Framework này - xin cám ơn!__*

## Solution

Project được xây dựng trên __IDE Visual Studio 2017__ với __Windown SDK 10__ và dùng thư viện __DirectX9 SDK - June 2010.__ Hãy đảm bảo rằng môi trường phát triển của bạn có những thứ đó. Ngoài ra lời khuyên khi cài đặt __Directx SDK__ là nên cài đặt vào vị trí mặc định, đường nên chọn đường dẫn khác - sẽ gây khó khăn cho run Solution sau này.

1. __Giới thiệu về Solution__
 
   Solution bao gồm 4 project trong đó. Nội dung giải thích chi tiết của từng project sẽ có trong các file Readme khác.
   
   * _directx-dev-library_: Thư viện quan đến Directx
   * _game2d-dev-library_: Thư viện dành cho phát triển game2d
   * _ninjagaiden_: Project này dành cho game Ninja Gaiden. Nếu muốn làm game khác, chủ yếu thay đổi các nội dung trong đây để thành game bạn muốn
   * winmain: Project kết hết tất cả các Project trên để có thể run được

2. __Hướng dẫn run và sửa lỗi run__
	
   * Set project __winmain__ as Startup Project
   * Chuyển __Solution Platforms__ về x86 (Win32)
   * Thay đổi __Properties VC++ Directories__ của các projects: Nếu thư viện DirectX 9 SDK được cài đặt như bình thường thì không cần thực hiện cài đặt này. Thêm vào các giá trị được mô tả dưới đây.
     
     * Ở Project _directx-dev-library_:
        *  Mục *__Include Directories__*: _<đường dẫn thư mục DirectX 9 SDK>\Include_
        *  Mục *__Library Directories__*: _<đường dẫn thư mục DirectX 9 SDK>\Lib\x86_
     * Ở Project _game2d-dev-library_:
     * Ở Project _ninjagaiden_:
     * Ở Project _winmain_:
        *  Mục *__Include Directories__*: _<đường dẫn thư mục DirectX 9 SDK>\Include
   
3. __Bổ sung thông tin về lỗi run__

   Hiện tại thông tin về lỗi run và cách fix mình chỉ có được đến mức này. Nếu có phát hiện lỗi hoặc cách fix hãy liên hệ với mình.
   
   _Ngày 07-06-2019_

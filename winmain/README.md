# WinMain Project

Project ninjagaiden là một project __C++ Win32 Application__.  
Được viết ra nhằm kết hợp tất cả những project ở trên thành 1 ứng dụng game hoàn chỉnh có thể chạy được. Đây là project cuối cùng trong chuỗi project, nhưng thực ra nó nên được tạo sớm bởi không có trường hợp mà chúng ta code từ đầu đến cuối mà không chạy 1 lần nào để test từng giai đoạn cả :).


## Mô tả thư viện

Không có quá nhiều điều để nói trong project này, hầu hết nó cũng chỉ là mẫu có sẵn vì đây là cách để tạo ra một ứng dụng Win32 bằng C++. Chỉ có một vài thứ đáng lưu ý đó là:

1. __Resource__

   Nếu như các giá trị hằng trong project game của bạn được định nghĩa theo kiểu đường dẫn tương đối thì hãy đem các tập tin Resource đó đến đây, vì relative path được tính từng đây - project startup.
   
   Hãy tổ chức tài nguyên sao cho hợp lý và logic, tránh bối rối khi sử dụng để nó đấy :)
   
2. __Khởi tạo mọi thứ với WinMain()__
   
   * __directGraphic__ 
   * __directInput__
   * __directSound__
   * __gameWorld__
   * __keyHandler__ và __mouseHandler__ được kết thừa từ __KeyboardHandler__ và __MouseHandler__ đã được nói ở project __directx-dev-library__.

3. __Main Loop - Vòng lặp chính của chương trình__

   Khi mà vẫn chưa có lệnh thoát chương trình đến từ hệ điều hành, thì vòng lặp mãi tiếp tục. Mỗi một lần lặp như vậy được xem như 1 frame của game được cập nhật.  
   Khái niệm __FPS__ đã được nêu trước đó, từ FPS t có thể tính được thời gian cho mỗi frame, khi hết thời gian đó, chúng tat sẽ cập nhật thế giới game lại. Bao gồm 3 việc: 
   
    * Lấy thông tin input từ phương thức __processInput()__ của __directInput__.
    * Cập nhật thế giới game của chúng ta với khoảng thời gian giữa các frame thông qua phương thức __update()__.
    * Và cuối cùng __render()__ để phản hồi lại cho người dùng. 
   
4. __Xử lý input__

	Khi tạo 2 đối tượng có kiểu class __WinKeyHandler__ và __WinMouseHandler__ hãy địnhh nghĩa lại cho phù hợp với thông tin tín hiệu input mà chúng ta muốn xử lý.  
    Ở đây với game này chúng ta chỉ cần tính hiệu đến từ bàn phím để điều khiển nhân vật chính. Và nhân vật chính có phương thức __handleInput()__, nên hãy đem nó đến __onKeyState()__ của __keyHandler__.
 
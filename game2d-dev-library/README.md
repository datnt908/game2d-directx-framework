# Game2D-Dev-Library Project

Project game2d-dev-library là một project __C++ static library__.
Được viết ra nhằm cung cấp các hằng, hàm, class,... có liên quan đến các thành phần giúp phát triển game 2D trên nền tảng Windown với DirectX.

Project này được phát triển với sự phụ thuộc vào project __directx-dev-library__ trước đó.
Nên để có thể sử dụng thư viện trong project này, hãy đảm bảo rằng nó được đi chung bộ với project kia.

## Mô tả thư viện

Project này cung cấp các thành phần cơ bản cho phát triển game 2D được sử dụng trong đồ án môn học __Nhập môn phát triển game__. Như là, sprites, animation, collision, space partitioning, transformation,...

__Lưu ý__: Mọi vấn đế liên quan đến tọa độ trong phần này, nếu không được đề cập chi tiết thì được hiểu là tọa độ tính theo trục __y__ hướng lên.

### Collision - Va chạm

1. __Struct BoundaryBox__

   Cấu trúc dữ liệu như một hình chữ nhật, đại diện cho vùng giới hạn của một thứ mà chúng ta có nhu cầu sử dụng. Bao gồm vị trí __position__ được tính góc dưới bên trái của hình chữ nhật, kích thước __size__ của hình chữ nhật.

2. __Class MovementBox__

   Tương tự như __BoundaryBox__ nhưng có thêm tính chất dịch chuyển. Đại diện cho chuyển động của vật thể. Được sử dụng trong hàm xét va chạm __sweptAABB()__. Thuộc tính __dtPosition__ là độ lệch của vị trí bắt đầu chuyển động và kết thúc chuyển động nếu không có cản trở.

3. __Struct CollisionEvent__

   Là sự kiện va chạm, mang theo thông tin thời gian va chạm __colliTime__ với đối tượng __gameObj__ cùng đó là vector phản hồi va chạm __normal__.

   Chi tiết về cặp giá trị __colliTime__ và vector phản hồi __normal__ hãy xem trong hàm __sweptAABB()__ tại mục __Những vấn đề khác__.

### Object - Đối tượng

### Graphic - Đồ họa 

### Space Partitioning - Phân hoạch không gian

### Những vấn đề khác

1. __Helper Functions__

   * __checkAABB_Box()__ để kiểm tra hai boundary box có overlap nhau hay không
   * __sweptAABB()__ để tính toán và trả ra các kết quả của việc kiểm tra va chạm theo thuật toán sweptAABB. Theo thuật toán swept trong giáo trình [Nhập môn phát triển game][1] thì bản thân mình cảm thấy vẫn chưa đủ các kết quả mong muốn. Vì thế mình đã có vài thay đổi trong đó nhằm đạt được kết quả mà mình mong muốn.

     Thuật toán có khả năng kiểm tra trường hợp bị overlap trước khi bắt đầu chuyển động.       
     Có khả năng kiểm tra xem overlap nhưng hướng chuyển động là ra xa nhau thì không xem là va chạm  
     Chi tiết hoạt động có thể tham khảo thêm cũng như xem trong source code, dưới đây là mô tả về mô tả kết quả trả về

         normal == (0,0) và colliTime == 1.f thì không có va chạm
         normal == (0,0) và colliTime == 0.f thì có va chạm ngay từ đầu
         normal != (0,0) thì có va chạm trong khoản thời gian return

  * __transformWorldToView()__ biến đổi từ tọa độ thể giới __worldPos__ sang tọa độ view __viewPos__ với gốc tọa độ của view port là __orginPos__
  * __transformViewToWorld()__  biến đổi từ tọa độ view __viewdPos__ sang tọa độ thế giới __worldPos__ với gốc tọa độ của view port là __orginPos__
  * __printOnOutput()__ nếu có nhu cầu để debug nhưng gặp khó khăn vì vấn đề vòng lặp quá nhanh. Hãy dùng đến nó, nó sẽ print ra màn hình output ở Visual Studio

2. __Typedef và kiểu dữ liệu mới__

  * __typedef void(*EndAnimationEvent)()__ đây định nghĩa một kiểu dữ liệu mới là con trỏ hàm phụ vụ cho việc raise ra event khi kết thúc một animation
  * __typedef vector\<LPGAMEOBJ\> GAMEOBJS_V__ vector các con trỏ kiểu GameObject dùng trong hàm xét va chạm hàng loạt nhiều đối tượng.
  * __typedef unordered_map\<int, LPGAMEOBJ\> GAMEOBJS_U__ unordered map được sắp xếp theo id của game object
  * __typedef unordered_map\<int, GAMEOBJS_V\> GAMEOBJS_M__ unordered map chứa vector các game object phân theo từng loại game object

  Mục đích của từng loại sẽ được nêu trong phần viết nào có sử dụng đến nó.

[1]: http://tiny.cc/cpn07y "GiaoTrinhNMPTGame"

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

1. __Class GameObject__

   Abstract class đại diện cho đối tượng trong game, bao gồm các thuộc tính: vị trí trong world __position__, kích thước __size__ và vận tốc __velocity__.  
   Class __GameObject__ cung cấp các phương thức như __update()__ cập nhật thông tin trạng thái, thuộc tính sau 1 khoảng thời gian. __render()__ vẽ lên màn hình dựa trên trạng thái hiện tại. __getMoveBox()__ trả ra MOVEBOX cho việc xét va chạm.

2. __Class InteractiveObj__

   Được kế thừa từ class __GameObject__, class này dùng để bổ sung thêm phương thức xét va chạm giữa nó với một loạt các GameObject khác. 
   
   Phương thức __calculateColli()__ tính toán và trả ra các sự kiện va chạm (nếu có) với từng phần tử danh sách các GameObject được truyền vào. Ngoài ra cần có sự hỗ trợ của phương thức __sweptAABBex()__ để tính va chạm với 1 GameObject.

### Graphic - Đồ họa 

Có vài điều cần lưu ý trong phần đồ họa đó là về mặt bộ nhớ chính. Khi mà load game, thực chất chúng ta chỉ load mỗi loại tài nguyên một lần lên bộ nhớ chính nhằm tránh việc hao tốn vô lý. Vì thế hãy để ý xem chúng ta có đang hao phí bộ nhớ vô lý không nhá.  

Kiểu dữ liệu __Texture__ mà đã đề cập đến ở project trước, thực chất là con trỏ - vì thế chỉ cần đừng gọi nhiều hơn 1 lần hàm __loadTexture()__ cho một hình muốn thì nó sẽ không hao phí đâu :)

1. __Class TextureCollection__

   Sau khi load một ảnh lên thàn texture bằng hàm __loadTexture()__ chúng ta cần lưu trữ chúng ở đâu đấy mà khi cần có thể gọi đến trực tiếp, vì thế __TextureCollection__ được thiết kế theo singleton pattern. 
   
   Thuộc tính __textures__ dùng để lưu các texture theo kiểu thứ tự ID người dùng tự đặt để khi cần có thể dùng ID lấy ra texture cần sử dụng. Và dĩ nhiên phải cung cấp 2 phương thức __addTexture()__ và __getTexture()__ để thêm và lấy texture theo ID. __addTexture()__ đã bao gồm hàm __loadTexture()__ rồi, vì thế chỉ việc truyền tham số cần thiết thì sẽ tự động load và thêm vào thuộc tính __textures__ thôi.
   
2. __Class Sprite__

   Về mặt bản chất, sprite thực chất là texture nhưng có một vùng giới hạn để khi vẽ texture ra, chỉ vẽ trong vùng giới hạn đó. Vì thế trong class __Spritte__ ngoài thuộc tính __texture__ được lấy từ __TextureCollection__ thì còn một thuộc tính là __spriteRect__ để lưu vùng giới hạn đó.
   
   Ngoài ra còn một số thứ hỗ trợ cho va chạm là __size__, __center__ mà mình sẽ trình bày trong project __ninjagaiden__ để các bạn hiểu thêm. Còn lại là __scaleMatrix__ và __rotateMatrix__ là thuộc về phép biến đổi nhằm hỗ trợ scale, flip, rotate hình ảnh.

3. __Class Animation__

   Animation thực chất là việc vẽ liên tiếp các sprite theo một thứ tự nhất định và có khoảng thời gian để chuyển đổi sprite - khi đó thị giác có hiện tượng lưu ảnh tạo nên cảm giác chuyển động.  
   
   * Do đó cần có các thuộc tính __frames__ để lưu các sprite.  
   * __dtFrameTime__ khoảng cách thời gian để chuyển từ sprite này sang sprite khác.
   * __curFrame__ để cho biết hiện chúng ta đang vẽ sprite nào trong các sprite 
   * __lastFrameTime__ bộ đếm thời gian để biết khi nào chúng ta sẽ chuyển sprite.
   * Ngoài ra __endAniEvent__ (xem __Những vấn đề khác__ mục __2__) để raise event khi kết thúc animation. Đặt ở đây vì chỉ mỗi class này là có khả năng biết được khi nào kết thúc 1 animation.

   Có khá nhiều phương thức được cung cấp bởi __Animation__ bao gồm:
   
   * __addFrame()__ để thêm một sprite mới vào cuối chuỗi sprite hiện có, nên hãy đảm bảo thứ tự thêm sprite cho đúng.
   * __render()__ để vẽ một animation - tức là vẽ sprite hiện tại ra và cũng sẽ có cập nhật __curFrame__ nếu đến thời điểm chuyển.
   * __getCurFrameSize()__ và __getCurFrameCenter()__ để lấy ra hai thuộc tính tương ứng.
   * __setScale()__ và __setRotate()__ để biến đối hình so với hình gốc chưa được biến đổi.

4. __Class AnimationCollection__

   Tương tự như __TextureAnimation__, tuy nhiên class này sẽ làm thuộc tính cho riêng từng loại GameObject trong game của bạn, cho nến không có singleton pattern.  
   Và hiển như sẽ cung cấp các phương thức __addAnimation()__ và __getAnimation()__ để thêm vào lấy ra một Animation theo ID.

### Space Partitioning - Phân hoạch không gian

Về nguyên lý cũng như những thứ cơ bản về phân hoạch không gian, các bạn có thể tham khảo trong giáo trình [Nhập môn phát triển game][1]. Mình ở đây chỉ giải thích về mặt triển khai thành source code.

Và lưu ý là việc load của phân hoạch không gian phụ thuộc và cấu trúc dữ liệu file lưu phân hoạch không gian của từng tình huống cụ thể, nên khi dùng hãy đảm bảo tính phù hợp của tình huống.

1. __Class Node__

   Thông tin cần thiết cho một Node có lẽ là định danh cho Node đó __id__, phạm vi của Node đó __nodeRect__ và danh sách các ID của GameObject __objIDs__.  
   Phương thức __loadFromString()__ cần đảm bảo sự phù hợp về cách load thông tin vào trong Node.
   Phương thức __getObjIDsInView()__ là kiểm tra xem khung nhìn có "đến" với Node đó chưa, và trả ra danh sách ID của các GameObject trong đó nhằm mục đích update đối tượng sau này.

2. __Class SpacePartitioning__

   __SpacePartitioning__ dùng để lưu trữ các Node và duyệt tổng hợp cho toàn bộ Node trong thế giới game.  
   Tương tự vơi hàm __loadFromString()__ ở __Node__ hãy đảm bảo rằng cách load lên phù hợp với file lưu trữ.  
   Và hàm __getObjIDsInView()__ lúc này có nhiệm vụ tổng hợp tất cả ID của các GameObject có được trong từng Node thành một danh sách lớn và __không trùng lắp__ nếu không sẽ có trường hợp một vài GameObject update đến nhiều hơn 1 lần.

### Những vấn đề khác

1. __Class BaseTileMap__

   Các bạn hãy tự tìm hiểu thêm về TileMap là gì, tại sao chúng ta cần đến TileMap. Còn bây giờ mình sẽ nói về abstract class __BaseTileMap__. Thành phần cần có trong TileMap bao gồm:
   
    * Một bộ sprite (có thể gọi là TileSet hoặc SpriteSet) dùng để  lưu về mặt hình ảnh của TileMap: __spriteSet__
    * Một ma trận số để lưu vị trí nào cần vẽ sprite nào: __matrixMap__
    * Vì là cần có thêm thuộc tính vị trí và kích thước cho TileMap trong thế giới game nên sẽ cho kế thừa từ __GameObject__
    * Ngoài ra còn cần có kích thước của 1 sprite: __spriteSize__

   Các phương thức cho một TileMap quan trọng là các phương thức load:
   
    * __loadSpriteSet()__: truyền vào một texture của TileSet và kích thước 1 sprite, nó sẽ load thành bộ sprite cho bạn
    * __loadMatrixMap()__ để đưa vào ma trận chỉ số sprite cho từng vị trí tương ứng
    * Hàm pure virtual __loadResource()__ để khi tạo class TileMap cho riêng bạn thì có thể tái định nghĩa lại cách load cho phù hợp, ngoài ra còn có hàm __update()__
  
2. __Class BaseGameWorld__

   __Hãy chú ý__, phần này khác là quan trọng, để có thể xây dựng được class GameWorld cho từng game riêng biệt mà dự trên Solution này cũng mình cần phải này được cách mà nó hoạt động.
   
   GameWorld tượng trưng cho thế giới game mà bạn đang phát triển. GameWorld khá là trừu tượng vì nó không thể nhìn thấy trực quan được. Chỉ khi thông qua hàm __render()__ nó mới được thể hiện lên cho người dùng nhìn thấy.
   
   Trong tư duy của mình với môn học __Nhập môn phát triển game__ này thì dù cho có là giáo viên cho tựa game nào đi nữa, cũng phải có những thuộc tính tối thiểu này.
   
    * Danh sách các GameObject có trong thế giới: __gameObjects__
    * Phân hoạch không gian: __spacePart__
    * Camera để biểu thị khung nhìn đang ở đâu trong thế giới game: __camera__
    
   Ngoài ra để cho thuận tiện, mình đã thêm một vài thuộc tính phụ trợ cho nó:

    * Ma trận GameObject cần update được phân theo từng loại GameObject trong thế giới game: __inProcObjs__
    * Có một vài đối tượng mà chúng ta cần update liên tục không thực hiện phân hoạch: __alwayUpdate__

   Về mặt phương thức thì __BaseGameWorld__ cung cấp nhữn phương thức sau:
   
    * 3 pure virtual __initialize()__, __update()__ và __render()__ cần định nghĩa cho class __GameWorld__ cụ thể của từng game.
    * __addAlwayUpdate()__ thêm một đối tượng thành đối tượng thường xuyên update, và kèm theo loại để giúp có tổ chức hơn.
    * __deleteObject()__ xóa một GameObject ra khỏi GameWorld - đây được xem như các "chết" cho đối tượng đó trong thế giới game.
    * __updateInProcObjsList()__ cập nhật __inProcObjs__ cho phù hợp để có được danh sách các GameObject cần update (bao gồm obj phân hoạch và obj thường xuyên update).
    
3. __Helper Functions__

   * __checkAABB_Box()__ để kiểm tra hai boundary box có overlap nhau hay không
   * __sweptAABB()__ để tính toán và trả ra các kết quả của việc kiểm tra va chạm theo thuật toán sweptAABB. Theo thuật toán swept trong giáo trình [Nhập môn phát triển game][1] thì bản thân mình cảm thấy vẫn chưa đủ các kết quả mong muốn. Vì thế mình đã có vài thay đổi trong đó nhằm đạt được kết quả mà mình mong muốn.

     Thuật toán có khả năng kiểm tra trường hợp bị overlap trước khi bắt đầu chuyển động.       
     Có khả năng kiểm tra xem overlap nhưng hướng chuyển động là ra xa nhau thì không xem là va chạm  
     Chi tiết hoạt động có thể tham khảo thêm cũng như xem trong source code, dưới đây là mô tả về mô tả kết quả trả về

         normal == (0,0) và colliTime == 1.f thì không có va chạm
         normal == (0,0) và colliTime == 0.f thì có va chạm ngay từ đầu (overlap)
         normal != (0,0) thì có va chạm trong khoản thời gian return

   * __transformWorldToView()__ biến đổi từ tọa độ thể giới __worldPos__ sang tọa độ view __viewPos__ với gốc tọa độ của view port là __orginPos__
   * __transformViewToWorld()__  biến đổi từ tọa độ view __viewdPos__ sang tọa độ thế giới __worldPos__ với gốc tọa độ của view port là __orginPos__
   * __printOnOutput()__ nếu có nhu cầu để debug nhưng gặp khó khăn vì vấn đề vòng lặp quá nhanh. Hãy dùng đến nó, nó sẽ print ra màn hình output ở Visual Studio

4. __Typedef và kiểu dữ liệu mới__

   * __typedef void(*EndAnimationEvent)()__ đây định nghĩa một kiểu dữ liệu mới là con trỏ hàm phụ vụ cho việc raise ra event khi kết thúc một animation
   * __typedef vector\<LPGAMEOBJ\> GAMEOBJS_V__ vector các con trỏ kiểu GameObject dùng trong hàm xét va chạm hàng loạt nhiều đối tượng.
   * __typedef unordered_map\<int, LPGAMEOBJ\> GAMEOBJS_U__ unordered map được sắp xếp theo id của game object
   * __typedef unordered_map\<int, GAMEOBJS_V\> GAMEOBJS_M__ unordered map chứa vector các game object phân theo từng loại game object

   Mục đích của từng loại sẽ được nêu trong phần viết nào có sử dụng đến nó.

[1]: http://tiny.cc/cpn07y "GiaoTrinhNMPTGame"

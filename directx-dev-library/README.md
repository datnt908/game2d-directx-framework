# DirectX-Dev-Library Project

Project directx-dev-library là một project __C++ static library__. 
Được viết ra nhằm cung cấp các hằng, hàm, class,... có liên quan trực tiếp đến thư viện DirectX. 
Vì đây là lập trình game trên nền tảng Windown với DirectX nên việc sử dụng các thư viện liên quan đến DirectX khá là nhiều. 
Tuy nhiên với bộ thư viện cơ bản - DirectX SDK (June - 2010), bản thân thấy không được thuận tiện cho lắm.

Cho nên đây là project nhằm giúp cho việc thuận tiện (ít nhất là với cá nhân nhóm) trong việc phát triển.

## Mô tả thư viện

Thư viện bao gồm 5 class làm cốt lõi trong đó, và một vài thứ phụ trợ, cũng như source code của Utility được lấy từ internet về.

### Class DxGraphic

Được thiết kế theo singleton parttern. 
Bao gồm các thuộc tính, phương thức liên quan đến khởi tạo, xử lý đồ họa của DirectX, bao gồm:

* Trình xử lý đồ họa: __direct3d__, __direct3dDevice__
* Giải quyết vấn đề "nháy hình" bằng backbuffer: __backBuffer__
* Trình xử lý Sprite: __spriteHandler__
* Con trỏ cửa số của chương trình: __window__
* Kích thước hiển thị của cửa sổ: __clientSize__

Chức năng của DxGraphic bao gồm cung cấp khả năng:

* __initialize()__ để khởi tạo các thuộc tính liên quan.
* __getSpriteHandler()__ để lấy ra trình xử lý Sprite cho việc vẽ sprite sau này.

Ngoài ra, __DxGraphic__ còn có class friend là __GameWorld__ nhằm cho phép __GameWorld__ có quyền sử dụng các thuộc tính của nó cho việc render hình ảnh của các đối tượng trong __GameWorld__.

### Class DxInput

Được thiết kế theo singleton parttern. 
Bao gồm các thuộc tính, phương thức liên quan đến khởi tạo, xử lý sự kiện input của người dùng thông qua DirectX. 
__DxInput__ bao gồm __DxMouse__ và __DxKeyboard__ cho xử lý chuột và bàn phím. 
Nội dung chi tiết, bao gồm:

* Thuộc tính mang đối tượng DirectInput: __directInput__
* Thuộc tính kiểu class __DxMouse__ (xem chi tiết tại mục __Class DxMouse__): __directxMouse__
* Thuộc tính kiểu class __DxKeyboard__ (xem chi tiết tại mục __Class DxKeyboard): __directxKeyb__

Chức năng của DxInput bao gồm cung cấp khả năng:

* __initializeMouse()__ để cung cấp khả năng khởi tạo chuột. 
  
  Tham số truyền vào là con trỏ của đối tượng có kế thừa từ abstract class __MouseHandler__ - được nói chi tiết trong mục __Những vấn đề khác__.

* __initializeKeyb()__ để cung cấp khả năng khởi tạo bàn phím. 

  Tham số truyền vào tương tự như cách khởi tạo chuột - là một con trỏ của đối tượng có kế thừa từ abstract class __KeyboardHandler__.

* __getDirectInput()__ lấy ra thuộc tính __directInput__ phục vụ cho quá trình khởi tạo chuột và bàn phím (xem chi tiết tại __DxMouse__ và __DxKeyboard__).
* __processInput()__ được gọi sau mỗi vòng lặp chính của chương trình. Có nhiệm vụ xử lý dữ liệu input mà DirectX nhận được.

### Class DxMouse

Bao gồm các thuộc tính và phương thức liên quan đến các xử lý các tín hiệu chuột mà DirectX nhận được, bao gồm: 
khởi tạo __initialize()__ - và xử lý tín hiệu input của chuột __processInput()__.

* Thuộc tính mang đối tượng thiết bị input của directx: __inputMouse__
* Thuộc tính lưu giữ thông tin trạng thái của chuột: __mouseStates__
* Thuộc tính con trỏ abstract class __MouseHandler__: __mouseHandler__
* Phương thức __collectState()__ lấy ra trạng thái hiện tại của chuột.

### Class DxKeyboard

Bao gồm các thuộc tính và phương thức liên quan đến các xử lý các tín hiệu bàn phím mà DirectX nhận được, bao gồm: 
khởi tạo __initialize()__ - và xử lý tín hiệu input của bàn phím __processInput()__.

* Thuộc tính mang đối tượng thiết bị input của directx: __inputKeyb__
* Thuộc tính lưu giữ thông tin trạng thái của bàn phím (256 Virtual Key): __keyStates__
* Thuộc tính con trỏ abstract class __KeyboardHandler__: __keybHandler__
* Thuộc tính lưu giữ thông tin trạng thái bàn phím trong bộ đệm: __keyEvents__
* Phương thức __createDeviceDataBuffer()__ nhằm khởi tạo bộ đệm cho bàn phím
* Phương thức __collectState()__ lấy ra trạng thái hiện tại của bàn phím.
* Phương thức __collectBuffer()__ lấy ra các sự kiện tín hiệu phím nhấn trong bộ đệm.

  Vì __collectState()__ chỉ lấy ra trạng thái hiện tại của bàn phím. 
  Chương trình có một khoảng nghỉ giữa 2 lần loop (Frame Per Sec - mỗi Frame là một lần loop). Dù cho FPS có cao - khoảng nghỉ nhỏ, thì không có gì là chắc chắn rằng phím bạn nhấn trong khoảng thời gian đó có rơi vào thời điểm mà __collectState()__. Vì thế buffer là để chứa các sự kiện input phím trong khoảng nghỉ đó.

### Class DxSound

Được thiết kế theo singleton pattern.
Bao gồm các thuộc tính và phương thức liên quan đến xử lý âm thanh bằng DirectX.
Class có sử dụng đến source code __DSutil__, đây là source code thư viện nhằm sử dụng âm thanh trong DirectX. 
Thật ra, ở những phiên bản trước của DirectX9, __DSutil__ có thể tìm thấy trong thư mục thư viện __DirectX SDK__ tuy nhiên có vẽ như phiên bản June - 2010 thì không tìm thấy. 
Nên __DSutil__ và __dxutil__ trong thư mục __Utility__ được tìm trên internet.

* Thuộc tính đảm nhận nhiệm vụ quản lý các tác vụ âm thanh: __soundManager__
* Thuộc tính lưu trữ các âm thanh sau khi tải vào: __soundStorage__

Chức năng của __DxSound__ bao gồm cung cấp khả năng:

* __initialize()__ cung cấp khả năng khởi tạo
* __addSound()__ cung cấp khả năng load và thêm tập tin âm thành vào
* __playSound()__ phát ra âm thanh đã được load có kèm hiệu ứng âm thanh đơn giản
* __stopSound()__ dừng một đoạn âm thanh nếu nó đang được phát

### Những vấn đề khác

Ngoài những mục được giải thích bên dưới ra còn có các Define và Typedef nhằm thuận tiện hơn trong quá trình phát triển. Các bạn có thể xem thểm trong source code __DxHelper__

#### Helper Functions

* __loadTexture()__ để tải lên một ảnh thành texture với màu transparent được truyền làm tham số. 
  
  Đây là friend của __DxGraphic__ vì để load được texture chúng ta cần sử dụng thuộc tính trong đó, nhưng để tránh rắc rối khi gọi hàm nên đem __loadTexture()__ ra thành hàm friend.

    Texture loadTexture(LPCWSTR filepath, Color transparent);

#### Abstract class MouseHandler và KeyboardHandler

Mỗi abstract class có 3 pure virtual methods:

* __OnState()__ sẽ trả ra thông tin trạng thái hiện tại của thiết bị input.
* __OnPress()__ sẽ trả ra thông tin nút được nhấn của thiết bị input.
* __OnRelease()__ sẽ trả ra thông tin nút được thả ra của thiết bị input.

Để sử dụng được 2 class này, chúng ta cần tạo class mới kế thừa và định nghĩa lại 3 phương thức theo cách xử lý logic mà chương trình cần thiết. Khi đó, hàm __processInput()__ của __DxInput__ sẽ gọi đa hình xuống các hàm của class mới. Như vậy sẽ đảm bảo đúng xử lý logic input mà bản thân mong muốn.
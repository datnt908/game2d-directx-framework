# NinjaGaiden Project

Project ninjagaiden là một project __C++ static library__.
Được viết ra nhằm cung cấp các hằng, hàm, class,... có liên quan đến game NinjaGaiden phạm vi từ Stage 3.1 đến 3.3. Đây cũng sẽ là mẫu project nếu như muốn làm một game khác.

Project này được phát triển với sự phụ thuộc vào project __directx-dev-library__ và project __game2d-dev-library__ trước đó.
Nên để có thể sử dụng thư viện trong project này, hãy đảm bảo rằng nó được đi chung bộ với các project kia.

## Mô tả thư viện

Project này cung cấp các thành phần cơ bản cho phát triển game Ninja Gaiden NES bao gồm các Game Object như Enemies, Weapon, Items, Immortal Object,... tất tần tật những thứ liên quan đến phạm vi game đang làm.

__Lưu ý__:  
Mọi thiết kế dưới đây không phải là mẫu cho tất cả, đây chỉ là project mang tính tham khảo, tùy vào từng game mà có cách thiết kế khác nhau.  
Những thiết kế hướng đối tượng dưới đây không phải là chuẩn cho game này, nó phụ thuộc cao vào cách lập trình viên thiết kế. Đây chỉ là cách mà mình thấy mình phù hợp và thực hiện đơn giản.

### Immortal Objects

1. __Class ImmortalObj__

   ImmortalObj được xây dựng để dành cho các GameObject "bất tử" như là Ground, Water, Wall, Gate... Đặc điểm của chung của các loại này khiến mình gôm chúng lại là: 
   
   * Chúng không bị mất đi theo thời gian, như là việc main character có chém cũng không chết.
   * Chúng không gọi xét va chạm với đối tượng khác mà là để đối tượng khác xét va chạm đến.
   * Đối tượng không có vận tốc, không mang hình ảnh cụ thể.

   Vì khá là đơn giản nên class này khi kế thừa từ class __GameObject__, hai hàm __update()__ và __render()__ sẽ để rỗng. Chúng ta chỉ cần quan tâm đến 2 thuộc tính là __position__ và __size__ để khi lấy ra MoveBox được chính xác để tính toán va chạm.

2. __Class TileMap__

   TileMap đương nhiên sẽ được kế thừa từ class __BaseTileMap__ và sẽ thêm một vài thuộc tính, phương thức cần thiết cho game của chúng ta:
   
    * Thuộc tính __stage__ là kiểu enum __Stage__ nhằm cho biết màn chơi nào trong từ stage 3.1 đến stage 3.3.
    * Định nghĩa pure virtual __loadResource()__ cho phù hợp với cách load TileMap, ngoài ra __update()__ hãy để rỗng vì không cần thiết sử dụng đến.
    * Phương thức __loadStage()__ là bổ sung thêm để thuận tiện, nó sẽ load TileMap lên phù hợp với stage mà chúng ta truyền vào. Sẽ sử dụng đến khi chúng ta new game, restart, repawn.

3. __Struct Scoreboard__

   Nói về bảng điểm, để cho đơn giản thì mình có ý tưởng như sau: 1 Hình ảnh lưu bảng điểm trong đó là những thứ mà nó không thay đổi (như là title chẳng hạn). 2 là bảng chữ cái cần thiết cho những giá trị hiện thị.  
 Bảng điểm là điểm cập nhật thông tin cho người chơi, để nó thì singleton giúp chúng ta dễ dàng hơn trong việc cập nhật thông tin. Và hãy điểm qua thuộc tính và phương thức:
 
   * Thuộc tính __sprites__ chứa các hình ảnh cần thiết cho bảng điểm: gồm cái bảng điểm lớn, và các ký tự cho giá trị hiển thị.
   * Các thuộc tính còn lại sẽ là nơi lưu trữ giá trị cần hiển thị.
   * Để cho gọn, mình tách nó thành các hàm __render()__ riêng biệt cho từng giá trị cần render. Ý tưởng của việc render này là: chuyển đổi giá trị muốn hiển thị thành mảng các ký tự có thứ tự, để khi cần đế ký tự nào, chúng ta dùng chỉ số mà lấy ra được sprite tương ứng của ký tự đó.
   * Cuối cùng nhớ rằng định nghĩa các hàm còn lại đa hình cho phù hợp
  
### Items 

Dù cho có nhiều loại items khác nhau nhưng để cho đơn giản và có vẽ như là chúng ta cũng không cần thiết kế chi cho nhiều class. Hãy để 1 class __Item__ duy nhất là hết phần việc của nó:

   * Thuộc tính static __animations__ để đảm bảo rằng dù cho có nhiều đối tượng item được sinh ra trong khắp thế giới game thì tài nguyên chỉ nên load 1 lần.
   * Vì có nhiều loại item khác nhau, cũng như còn sự khác nhau về trạng thái, hình ảnh,... Hãy để 3 thuộc tính __icon__ là hình ảnh mà nó trước khi trở thành item rơi xuống đất, __kind__ để phân biệt loại item với chức năng cụ thể của từng loại, __state__ để cho biết nó đã trở thành 1 item có thể nhặt được hay chưa.
   * Chúng ta có tài nguyên kiểu static nên hãy cho nó khả năng __loadResource()__ và __releaseResource()__ ở dạng static.
   * Một vài hàm hỗ trợ xử lý cho phù hợp với logic game như: __handleCollisionWith...()__,  __onCollisionWithMain()__


### Enemies

Tương tự như item, mình không chia từng loại cụ thể mà chúng ta thấy nó có mặt trong game, mình gôm nhóm và cho kế thừa theo cách thức mà enemies hoạt động. Cụ thể có 3 nhóm mà cách hoạt động chúng có nét tương đồng.

1. __Class BaseEnemy__

   * Thuộc tính static __anicollectS__ giống với Item, đem hết các animation của các enemy load lên và hãy để ID lấy ra thứ bạn cần theo cách của riêng bạn.
   * Thuộc tính __enemyKind__ kiểu enum __ObjKind__ giúp phân biệt loại enemy cụ thể để có thể render ra chính xác. Cùng với nó sẽ là __state__ của enemy đó.
   * __direction__ cho biết hướng trái phải của enemy, __timeToDie__ cho thêm tí thời gian để render vài hiệu ứng nổ đẹp mắt.
   * Vì có 3 state cho enemy nên có 3 hàm xửu lý trạng thái cho phù hợp. __updateDeadState()__ là đa số giống nhau cho các loại enemy nên sẽ định nghĩa sẵn.
   * Phương thức virtual __onCollision()__ để xử lý sự kiện khi có va chạm cho phù hợp.

2. __Class MovingEnemy & Class StandingEnemy & Class BossEnemy__

   Hiển nhiên sẽ cho MovingEnemy kế thừa từ BaseEnemy, tuy nhiên có những trường hợp update các state là khác nhau về mặt xử lý cho từng loại enemy cụ thể. Hãy tạo những hàm hỗ trợ việc đó như __updateMoveStateForEnemy2()__, __updateAttkStateForEnemy4()__,... cho việc xử lý đó.
   
   Sau đó trong phương thức __update()__ chính hãy dùng switch để gọi đến cách update phù hợp với từng loại mà không bị phức tạp code.

   Class __StandingEnemy__ cũng tương tự, hãy cố gắng gôm chung những thứ giống nhau lại để code cho nhẹ nhàng hơn.

### Weapons

Tương tự như cả item và enemies. Mình chia Weapon thành 3 loại: quỹ đạo đi thẳng __StraightWeapon__, quỹ đạo parapol rơi __ParapolWeapon__ và quỹ đạo elip __BoomerangWeapon__.

  * Thuộc tính static __sprites__ lưu giữ hình ảnh của các loại weapon trong game.
  * Thuộc tính __icon__ kiểu enum Weapon làm ID để lấy ra sprite tương ứng mà render. Kèm theo hiệu ứng nổ nếu có với thuộc tính __isExplosion__.
  * Thuộc tính __timeToDie__ nhằm giới hạn sự tồn tại của object weapon đó, tránh sự sinh ra quá nhiều weapon mà không giải phóng khi hết tác dụng.
  * Một phương thức lạ hơn __updateMainCharWeapon()__ là dành cho loại vũ khí nào là của nhân vật chính, vì mình không chia cụ thể thành 1 class mới cho vũ khí của nhân vật chính nên phải cần đến nó.


### Main Character

Để hiểu rõ hơn về phần thiết kế nhân vật chính này, chúng ta cần nắm sơ bộ về state pattern. Hãy tham khảo chúng tại [Game Programming Pattern][1], vì cách thiết kế ở dưới đây được dựa trên tài liệu đấy.

1. __Class BaseState__

   Đây sẽ là state cơ sở cho các state khác kế thừa, chúng còn chức năng chứa các state cụ thể mà main character cần đến ở dạng các thuộc tính static.  
   
    * Phương thức __setState()__ giúp chúng ta chuyển đổi trạng thái nhân vật phù hợp hơn và vài hàm phụ trợ cho nó như là __setImmortalState()__, __setDeadState()__ và __setSpawnWeaponState()__.  
    * Thêm một vài phương thức giúp xử lý và chạm như __handleCollisionWith...()__ giúp cho việc code gọn gàng hơn, dễ hiểu hơn, module hơn. Và nhất là để cho chỉ khi state nào thực sự cần đến mới sử dụng, tránh việc xử lý va chạm tất cả các loại GameObject làm nặng nề.
    * Thêm những phương thức virtual giống với GameObject: __update()__, __render()__ và __getMoveBox()__ nhằm tái sử dụng code cho các state về sau để khi ở main character chỉ cần gọi đến và sử dụng chính xác nhờ tính đa hình.
    * Phương thức __handleKeyInput()__ sẽ là pure vì chắc chắn rằng cách nhận và xử lý tín hiệu điều khiển nhân vật mỗi state mỗi khác.
    * Ngoài ra hãy vì có một số state chúng ta cần đến sự kiện kết thúc animation, hãy cho nó một hàm friend: __void OnEndAttackAnimation()__ có kiểu hàm như kiểu con trỏ hàm đã định nghĩa trước đó. Và đem cách xử lý cần thiết vào trong đó.
    
2. __State Classes__

   Mình sẽ không đi vào giải thích từng state cụ thể bởi vì mỗi nhân vật, mỗi game mỗi khác. Nhưng có vài điều mình muốn lưu ý đó là:
   
    * Các hàm __handleCollisionWith...()__ khi định nghĩa xử lý cho chúng, hãy chọn định nghĩa nào mà có nhiều state sử dụng nhất, khi đó chúng ta lợi dụng tính kế thừa để không code lại. Các state khác sẽ có định nghĩa đặc biệt thì cần định nghĩa lại, nhưng sẽ là ít hơn.
    * Phương thức __update()__ ở từng state sẽ khác nhau hãy chắc lọc cách xử lý sao cho tăng tốc xử lý tốt nhất mà bạn có thể. Ví dụ như: ở state đứng yên (Idle) chắc chắn rằng không thể nào có sự dịch chuyển thì chúng ta không cần đến các xử lý va chạm về mặt chuyển động làm gì.
    * Phương thức __handleKeyInput()__ hãy tương tự tự như __update()__.

3. __Class MainCharacter__

   Thiết kế singleton pattern vì chúng ta sẽ cần nó cho sau này.  
   Hãy cho MainCharacter kế thừa từ __InteractiveObj__ để có khả năng xét va chạm đến các GameObject khác. Thêm các hằng số cần thiết cho nó. Đặt state classes làm friend class giúp lấy dữ liệu hiệu quả hơn.  
   Việc định nghĩa lại các phương thức __update()__, __render()__ và __getMoveBox()__ thực chất là gọi ra hàm của state hiện tại của main character. Hãy xem qua các thuộc tính và phương thức cần chú ý:
   
    * __state__ là con trỏ sẽ trỏ đến state hiện tại của main character, nó sẽ dùng để gọi đa hình xuống các phương thức cần thiết của state cụ thể.
    * __animations__ chứa tất cả các hoạt ảnh của main character. Ở đây, mỗi state sẽ có 1 animation tương ứng.
    * Thuộc tính __direction__ để biểu thị hướng trái phải của main character. Được dùng với __setDirection()__ và __setScale()__ để vẽ nhân vật đúng hướng.
    * Main character của chúng ta có khả năng phóng phi tiêu. Mình cho nó 1 phi tiêu mỗi lần phóng, hãy để 1 con trỏ __weapon__ lưu giữ nó. Bên cạnh đó đương nhiên sẽ cần hàm __updateWeapon()__ cho nó.
    * __initialize()__ và __loadResource()__ để khởi tạo những giá trị mặc định cho main character cũng như load tài nguyên cho nó.


### Những vấn đề khác

1. __Class GameWorld__

   Đây sẽ là thế giới game của chúng ta, với Ninja Gaiden thì có gì nhỉ :>?
   
    * __tileMap__ cho 3 stage trong phạm vi project.
    * __scoreBar__ cho bảng điểm hiện thị thông tin người chơi cần.
    * và __mainChar__ độc lập cho dễ xử lý.
    * Các hàm hỗ trợ __loadResource()__ và __loadGameObjs()__ giúp lấy dữ liệu từ bộ nhớ phụ (các file text lưu giữ thông tin cần thiết) lên thành các thành phần cho thế giới game.
    * Còn có các phương thức __initialize()__ khi lần đầu khởi chạy game, __newGame()__ khi mới bắt đầu hoặc khi chết hết mạng rồi, __respawn()__ khi vẫn còn mạng nhưng lại không may ngủm củ tỏi và __nextStage()__ khi đến được __Gate__ qua màn tiếp thep. 
    
2. __Các Helper__

   Tạo ra các hằng, các enum và helper functions cần thiết cho game (xem chi tiết trong source code) chúng ta bao gồm:
   
    * Hằng cho các tài nguyên trong game như đường dẫn file: nếu là relative thì được tính từ project startup
    * Hằng các giá trị cần thiết như ID texture, cài đặt hệ thống, các giá trị vận hành game,...
    * Các enum __ObjKind__ loại đối tượng trong game, __ItemKind__, __Stage__.
    * Helper functions __loadAllTexture()__, __loadSounds()__ để load tài nguyên.
    
[1]: http://gameprogrammingpatterns.com/state.html "GameProgrammingPattern"

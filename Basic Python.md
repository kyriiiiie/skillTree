# Basic Python

## topics

- Variable
- Array
- If

### variable

- String
  - title()
  - upper(), lower()
  - \t, \n
  - rstrip(), lstrip(), strip()
- Number
  - 3 ** 3 = 3 ^ 3
  - str(), int(), 类型转换

### Array

- array[-1]返回最后一个列表元素
- 添加
  - append(e): 在列表尾添加元素
  - insert(index,e): 在列表中插入元素
- 删除
  - del array[index]
  - pop(): 弹出列表末尾元素, pop(index)
  - 如果删除后不继续使用就用del, 要继续使用就用pop
  - remove(): 根据值删除 （只删除列表中第一个指定的值）

- 组织

  - 排序
    - sort(): 按字母序排序, array.sort(reverse=True)
    - sorted(): 临时排序， array.sorted(reverse=True)
    - 非全小写时，有多种解读大写的方式，需要指定准确的排序顺序
  - 反转
    - reverse()
  - Length: len(array)

- Operate array

  - traverse

    - ```python
      for element in array:
      	print(element)
      ```

  - range(): 生成一系列数字,

    - ```python
      for value in range(1,5):
      	print(value)
      #output: 1,2,3,4
      #可以指定步长 range(1,6,2)
      ```

  - list(): 将range()的结果直接转换为列表

    ```python
    numbers = list(range(1,6))
    print(numbers)
    #output: [1,2,3,4,5]
    ```

  - min(), max(), sum()

  - 列表解析：快速生成列表

    - ```python
      squares = [value**2 for value in range(1,11)]
      print(squares)
      #output:[1,4,9,16,25,36,49,64,81,100]
      ```

  - 切片

  - ```python
    players = ['charles','martina','michael','florence','eli']
    print(players[1:4])
    #output: m,f,e
    #没有指定索引就默认表头或表尾，-3也可以用
    ```

    ```python
    players = ['charles', 'martina', 'florence', 'eli']
    for player in players[:3]:
    	print(player.title())
    ```

  - copy array

  - ```python
    my_foods = ['p','f','c']
    friend_foods = my_foods[:]
    #friend_foods = my_foods不行，两个指向同一列表
    ```

- 元组（pyhton将不能修改的值称为不可变的，不可变的列表被称为元组）

- ```python
  dimensions = (200,50)
  print(dimensions[0])
  #dimensions为元组，不可修改里面的值，但可以全部重新赋值
  ```

### if statement

- 使用 and检查多个条件

- ```python
  (age_0 >= 21) and (age_1 >= 21)
  ```

- 用or检查多个条件

- ```python
  age_0 >= 21 or age_1 >= 21
  ```

- 检查特定值是否包含/不包含在列表中

  ```python
  requested_toppings = ['mushrooms','onions','pineapple']
  print('mushrooms' in requested_toppings)
  #output: True
  if 'sadfsasd' not in requested_toppings:
  	print('hh')
  #output: hh    
  ```

- if语句

  ```python
  #if
  if conditional_test:
      do something
  #if-else
  if age >= 18:
  	print("a")
  else:
      print("b")
  #if-elseif-else:
  if age < 4:
      price = 0
  elif age < 18:
      price = 5
  elif age < 65:
      price = 10
  ```

- 检查列表是否为空

- ```python
  requested_toppings = []
  if requested_toppings:
  	for requested_topping in requested_toppings:
  		print("Adding " + requested_topping + ".") 						print("\nFinished making your pizza!")
  else:
  	print("Are you sure you want a plain pizza?")
  ```

### Dictionary(map)

- 初始化和访问

- ```python
  #创建空字典
  dic = {}
  #普通初始化
  alien_0 = {'color': 'green', 'points': 5}
  new_points = alien_0['points']
  print("You just earned " + str(new_points) + " points!")
  ```

- 添加键-值对

- ```python
  alien_0 = {'color': 'green', 'points': 5} print(alien_0)
  alien_0['x_position'] = 0 
  alien_0['y_position'] = 25
  print(alien_0)
  ```

- 删除键-值对

- ```python
  alien_0 = {'color': 'green', 'points': 5} 
  print(alien_0)
  del alien_0['points'] 
  print(alien_0)
  ```

- 遍历字典

  - ```python
    #items()返回键-值对的一个列表
    user_0 = {
    'username': 'efermi', 'first': 'enrico', 'last': 'fermi',
    }
    for key, value in user_0.items(): 
        print("\nKey: " + key)
    	print("Value: " + value)
    #遍历所有键,keys()
    for name in favorite_languages.keys():
    #按字典序遍历所有键
    for name in sorted(favorite_languages.keys()):
    #遍历所有值
    for language in favorite_languages.values():
    #剔除重复项
    for language in set(favorite_languages.values()):
    ```

- 嵌套：将一系列字典存储在列表中，或将列表作为值存储在字典中，这称为嵌套

  - 字典中存储字典

  - ```python
    users = { 'aeinstein': {
    'first': 'albert', 'last': 'einstein', 'location': 'princeton', },
    'mcurie': {
    'first': 'marie', 'last': 'curie', 'location': 'paris', },
    }
    for username, user_info in users.items():
    	print("\nUsername: " + username)
    	full_name = user_info['first'] + " " + user_info['last'] 	 location = user_info['location']
    	print("\tFull name: " + full_name.title()) 					print("\tLocation: " + location.title())
    ```

### Input and while loop

- 函数input()工作原理

  - 函数input() 接受一个参数:即要向用户显示的提示 或说明

- ```python
  message = input("Tell me something, and I will repeat it back to you: ") 
  print(message)
  #output: Tell me something, and I will repeat it back to you: Hello everyone! Hello everyone!
  ```

- int()获取数值输入

- ```python
  height = input("How tall are you, in inches? ") height = int(height)
  ```

- While loop

  - ```python
    responses = {}
    # 设置一个标志，指出调查是否继续 polling_active = True
    while polling_active:
    # 提示输入被调查者的名字和回答
    name = input("\nWhat is your name? ")
    response = input("Which mountain would you like to climb someday? ")
    # 将答卷存储在字典中 responses[name] = response
    # 看看是否还有人要参与调查
    repeat = input("Would you like to let another person respond? (yes/ no) ")
    if repeat == 'no': polling_active = False
    # 调查结束，显示结果
    print("\n--- Poll Results ---")
    for name, response in responses.items():
    	print(name + " would like to climb " + response + ".")
    ```

### Function

- 定义函数

  - ```python
    def greet_user():
        print("Hello!")
    greet_user()
    #向函数传递信息
    def greet_user(username):
    	print("Hello, " + username.title() + "!")
    greet_user('jesse')
    ```

- 关键字实参

  - 是传递给函数的名称—值对。你直接在实参中将名称和值关联起来了，因此向函数传递实参时不会混淆(不会得到名为Hamster的harry这样的结果)。关键字实参让你无需考虑函数调用中的实参顺序，还清楚地指出了函数调用中各个值的用途。

  - ```python
    def describe_pet(animal_type, pet_name):
    	print("\nI have a " + animal_type + ".")
    	print("My " + animal_type + "'s name is " + pet_name.title() + ".")
    describe_pet(animal_type='hamster', pet_name='harry')
    ```

- 默认值

  - 给形参指定默认值后，可在函数调用中省略相应的实参

  - ```python
    def describe_pet(pet_name, animal_type='dog'):
    	print("\nI have a " + animal_type + ".")
    	print("My " + animal_type + "'s name is " + pet_name.title() + ".")
    describe_pet(pet_name='willie')
    #describe_pet('willie')也可以，这里视为位置实参
    #使用默认值时，在形参列表中必须先列出没有默认值的形参，再列出有默认值的实参
    ```

- 在函数中修改列表

  - 将列表传递给函数后，函数就可对其进行修改。在函数中对这个列表所做的任何修改都是永久性的

  - ```python
    unprinted_designs = ['iphone case', 'robot pendant', 'dodecahedron']
    completed_models = []
    while unprinted_designs:
    	current_design = unprinted_designs.pop()
    	print("Printing model: " + current_design)
    	completed_models.append(current_design)
    
    print("\nThe following models have been printed:")
    print(completed_models)
    print(unprinted_designs)
    #The following models have been printed:
    #['dodecahedron', 'robot pendant', 'iphone case']
    #[]
    ```

  - 禁止函数修改列表

  - ```python
    function_name(list_name[:])
    #切片表示法[:] 创建列表的副本
    ```

- 传递任意数量的实参

  - 形参名*toppings 中的星号让Python创建一个名为toppings 的空元组，并将收到的所有值都封装到这个元组中

  - ```python
    def make_pizza(*toppings):
    	print("\nMaking a pizza with the following toppings:") for 	   topping in toppings:
    		print("- " + topping)
    make_pizza('pepperoni')
    make_pizza('mushrooms', 'green peppers', 'extra cheese')
    ```

  - 如果要让函数接受不同类型的实参，必须在函数定义中将接纳任意数量实参的形参放在最后

    ```python
    def make_pizza(size, *toppings):
    make_pizza(12, 'mushrooms', 'green peppers', 'extra cheese')
    ```

  - 有时候，需要接受任意数量的实参，但预先不知道传递给函数的会是什么样的信息。在这种情况下，可将函数编写成能够接受任意数量的键—值对——调用语句提供了多少就接受多少

  - ```python
    #形参**user_info 中的两个星号让Python创建一个名为user_info 的 空字典，并将收到的所有名称—值对都封装到这个字典中。在这个函数中，可以像访问其他字典那样访问user_info 中的名称—值对
    def build_profile(first, last, **user_info): 
    	profile = {}
        profile['first_name'] = first 
        profile['last_name'] = last
    	for key, value in user_info.items(): 
            profile[key] = value
    	return profile
    
    user_profile = build_profile('albert', 'einstein', location='princeton',field='physics')
    print(user_profile)
    ```

- 将函数储存在模块中

  - 将函数存储在被称为模块 的独立文件中， 再将模块导入 到主程序中。import 语句允许在当前运行的程序文件中使用模块中的代码。 

  - ```python
    #pizza.py
    def make_pizza(size, *toppings):
        print("\nMaking a " + str(size) +
            "-inch pizza with the following toppings:")
        for topping in toppings:
            print("- " + topping)
    #making_pizza.py
    import pizza
    pizza.make_pizza(16, 'pepperoni')
    pizza.make_pizza(12, 'mushrooms', 'green peppers', 'extra cheese')
    ```

  - 导入特定函数

  - ```python
    from module_name import function_name
    #用逗号分隔函数名
    from module_name import function_0, function_1, function_2
    #此时无须用.
    from pizza import make_pizza
    make_pizza(16, 'pepperoni')
    make_pizza(12, 'mushrooms', 'green peppers', 'extra cheese')
    ```

  - 用as给函数，模块指别名(避免重名)

  - ```python
    #function
    from pizza import make_pizza as mp
    mp(16, 'pepperoni')
    mp(12, 'mushrooms', 'green peppers', 'extra cheese')
    #module
    import pizza as p
    p.make_pizza(16, 'pepperoni')
    p.make_pizza(12, 'mushrooms', 'green peppers', 'extra cheese')
    ```

  - 导入模块中所有函数

  - ```python
    #不需要.但不推荐使用
    from pizza import *
    make_pizza(16, 'pepperoni')
    make_pizza(12, 'mushrooms', 'green peppers', 'extra cheese')
    ```

    
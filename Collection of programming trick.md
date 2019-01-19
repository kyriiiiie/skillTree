# Collection of small trick

- `%2 == &1`
  - &是一种位运算符，相当于对每位做AND，速度更快
  - https://www.cprogramming.com/tutorial/bitwise_operators.html

- `用memset填充数组`

  - 填充0: memset(arr, 0, sizeof(arr));

- 用`0x3f3f3f3f`表示无穷大，用`0xc0c0c0c0`表示无穷小

  - 0x3f3f3f3f

    - 十进制是1061109567，是10^9级别的，可以作为无穷大
    - 相加不会溢出
    - 将某个数组赋值为无穷大，可以直接用 memset(a, 0x3f, sizeof(a))

  - ```
    #define MaxN  0x3f3f3f3f
    #define MinN  0xc0c0c0c0
    
    int main(void)
    {
        printf("%d %d\n",MaxN,MinN);
        //1061109567, -1061109568
        return 0;
    }
    ```

    
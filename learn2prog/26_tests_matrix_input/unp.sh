# 这个命令会创建一个包含不可打印字符的10x10文件
{
  echo "normal_one"
  echo "normal_two"
  echo "line_three"
  echo "line_four_"
  # 关键行：包含一个嵌入的 NULL 字节 (\x00)
  # 'line' + NULL + 'five_' = 4 + 1 + 5 = 10 字节
  printf 'line\x00five_\n'
  # 这一行包含其他控制字符，但不会导致strlen失败
  # 'bell' + BELL(\x07) + 'and' + VT(\x0b) + 'vt' = 4+1+3+1+1 = 10 字节
  printf 'bell\x07and\x0bvt\n'
  echo "line_seven"
  echo "line_eight"
  echo "line_nine_"
  echo "line_ten__"
} > unprintable_test.txt

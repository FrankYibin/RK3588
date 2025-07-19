import pandas as pd

# 读取 CSV 文件
csv_file = 'output.csv'
df = pd.read_csv(csv_file)

# 保存为 Excel 文件
excel_file = 'output.xlsx'
df.to_excel(excel_file, index=False)  # index=False 表示不保存行索引
print(f"CSV 文件已成功转换为 Excel 文件：{excel_file}")

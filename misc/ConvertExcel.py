import pandas as pd
import argparse
import os
import time
from pathlib import Path
from datetime import datetime

def is_usb_path(file_path):
    """检查文件路径是否在U盘或可移动媒体上"""
    return any(mount_point in file_path for mount_point in ["/run/media/", "/media/", "/mnt/"])

def sync_filesystem():
    """同步文件系统缓存到磁盘"""
    try:
        os.sync()
        print("Synced filesystem")
    except:
        pass

def write_excel_with_fallback(df, excel_file):
    """尝试多种引擎写入Excel文件"""
    engines = [
        ('xlsxwriter', 'xlsxwriter engine'),
        ('openpyxl', 'openpyxl engine'),
        (None, 'default engine')
    ]
    
    for engine, description in engines:
        try:
            if engine:
                df.to_excel(excel_file, index=False, engine=engine)
            else:
                df.to_excel(excel_file, index=False)
            print(f"Used {description}")
            return True
        except Exception as e:
            print(f"{description} failed: {e}")
            continue
    
    return False

def validate_excel_file(excel_file):
    """验证Excel文件是否成功创建"""
    if not os.path.exists(excel_file):
        print(f"✗ 错误：文件未创建：{excel_file}")
        return False
    
    file_size = os.path.getsize(excel_file)
    if file_size == 0:
        print(f"✗ 错误：生成的文件大小为0：{excel_file}")
        return False
    
    # 获取文件修改时间
    import stat
    file_stat = os.stat(excel_file)
    mod_time = datetime.fromtimestamp(file_stat.st_mtime)
    
    print(f"✓ 成功创建Excel文件：{excel_file} ({file_size/1024:.1f} KB)")
    print(f"  文件修改时间：{mod_time.strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"  当前系统时间：{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    
    return True
    
    print(f"✓ 成功创建Excel文件：{excel_file} ({file_size/1024:.1f} KB)")
    return True

def show_data_preview(df, num_rows=3):
    """显示数据预览，减少输出长度"""
    print(f"前{num_rows}行数据预览:")
    print(df.head(num_rows).to_string())
    print()
def main():
    parser = argparse.ArgumentParser(description='Convert CSV to Excel using pandas')
    parser.add_argument('csv_file', nargs='?', default='output.csv', 
                       help='Input CSV file path (default: output.csv)')
    parser.add_argument('excel_file', nargs='?', default=None,
                       help='Output Excel file path (optional, auto-generated if not specified)')
    parser.add_argument('-o', '--output', 
                       help='Alternative way to specify output Excel file path')
    parser.add_argument('--preview-rows', type=int, default=3,
                       help='Number of rows to show in data preview (default: 3)')
    
    args = parser.parse_args()
    
    csv_file = args.csv_file
    
    # 确定输出文件名的优先级：命令行第二个参数 > -o选项 > 自动生成
    if args.excel_file:
        excel_file = args.excel_file
    elif args.output:
        excel_file = args.output
    else:
        # 从CSV文件名生成Excel文件名
        csv_path = Path(csv_file)
        excel_file = csv_path.with_suffix('.xlsx').name
    
    print("CSV to Excel Converter")
    print("=" * 30)
    
    # 检查输入文件
    if not os.path.exists(csv_file):
        print(f"Error: {csv_file} not found!")
        return 1
    
    file_size = os.path.getsize(csv_file)
    print(f"Input: {csv_file} ({file_size/1024:.1f} KB)")
    print(f"Output: {excel_file}")
    print()
    
    try:
        # 读取并验证CSV文件
        df = pd.read_csv(csv_file)
        print(f"Loaded CSV: {df.shape[0]} rows × {df.shape[1]} columns")
        
        if df.empty:
            print("警告：DataFrame是空的！")
            return 1
        
        # 显示数据预览
        show_data_preview(df, args.preview_rows)
        
        # 确保输出目录存在
        output_dir = os.path.dirname(excel_file)
        if output_dir and not os.path.exists(output_dir):
            print(f"Creating directory: {output_dir}")
            os.makedirs(output_dir, exist_ok=True)
        
        # 写入Excel文件
        print(f"Writing to: {excel_file}")
        if is_usb_path(excel_file):
            print("检测到U盘路径，使用兼容模式...")
        
        if not write_excel_with_fallback(df, excel_file):
            print("✗ 所有Excel引擎都失败了")
            return 1
        
        # U盘需要额外的同步处理
        if is_usb_path(excel_file):
            print("同步文件系统到U盘...")
            time.sleep(1.0)  # 给U盘更多时间
            sync_filesystem()
            time.sleep(0.5)  # 再等待一下
            
            # 尝试手动设置文件时间为当前时间
            try:
                current_time = time.time()
                # 为Windows兼容性，尝试设置本地时间戳
                local_time = datetime.now()
                utc_time = datetime.utcnow()
                time_offset = (local_time - utc_time).total_seconds()
                
                print(f"时区信息: 本地时间={local_time.strftime('%H:%M:%S')}, UTC时间={utc_time.strftime('%H:%M:%S')}, 偏移={time_offset}秒")
                
                # 调整时间戳以补偿时区差异
                adjusted_time = current_time + time_offset
                os.utime(excel_file, (adjusted_time, adjusted_time))
                print(f"✓ 已更新文件时间戳 (本地时间: {local_time.strftime('%H:%M:%S')})")
                
                # 给文件系统更多时间来更新时间戳
                time.sleep(1.0)
                sync_filesystem()
                time.sleep(0.5)
                
            except Exception as e:
                print(f"✗ 无法更新文件时间戳: {e}")
        else:
            time.sleep(0.5)
            sync_filesystem()
        
        # 最终同步，确保所有更改都写入磁盘
        time.sleep(0.5)
        sync_filesystem()
        
        # 验证输出文件
        if validate_excel_file(excel_file):
            return 0
        else:
            return 1
        
    except PermissionError as e:
        print(f"权限错误：{e}")
        print("请检查输出目录的写入权限")
        return 1
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        return 1

if __name__ == "__main__":
    exit_code = main()
    exit(exit_code)

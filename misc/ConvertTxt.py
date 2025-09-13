import os
import shutil
import time
from datetime import datetime
import argparse
from pathlib import Path
import pandas as pd

def is_usb_path(file_path):
    """检查文件路径是否在U盘或可移动媒体上"""
    return any(mount_point in file_path for mount_point in ["/run/media/", "/media/", "/mnt/"])

def get_filesystem_info(file_path):
    """获取文件系统信息"""
    try:
        import subprocess
        result = subprocess.run(['df', '-T', file_path], 
                              capture_output=True, text=True)
        if result.returncode == 0:
            lines = result.stdout.strip().split('\n')
            if len(lines) >= 2:
                fs_info = lines[1].split()
                fs_type = fs_info[1] if len(fs_info) > 1 else "unknown"
                print(f"文件系统类型: {fs_type}")
                if fs_type.lower() in ['vfat', 'fat32', 'fat16']:
                    print("注意: FAT文件系统在Windows上可能显示UTC时间")
                return fs_type
    except:
        pass
    return None

def csv_to_txt(csv_file, txt_file):
    """将CSV文件转换为TXT文件"""
    try:
        print(f"Loading CSV file: {csv_file}")
        df = pd.read_csv(csv_file, encoding='utf-8-sig')
        print(f"CSV loaded: {df.shape[0]} rows × {df.shape[1]} columns")
        
        if df.empty:
            print("警告：CSV文件是空的！")
            return False
        
        print("Converting CSV to TXT format...")
        
        # 将DataFrame转换为制表符分隔的文本
        with open(txt_file, 'w', encoding='utf-8') as f:
            # 写入表头
            headers = list(df.columns)
            f.write('\t'.join(headers) + '\n')
            
            # 写入数据行
            for _, row in df.iterrows():
                row_data = []
                for value in row:
                    # 处理NaN值和特殊字符
                    if pd.isna(value):
                        row_data.append('')
                    else:
                        # 转换为字符串并清理
                        str_value = str(value).replace('\n', ' ').replace('\r', ' ').replace('\t', ' ')
                        row_data.append(str_value)
                f.write('\t'.join(row_data) + '\n')
        
        print("CSV to TXT conversion completed")
        return True
        
    except Exception as e:
        print(f"CSV to TXT conversion failed: {e}")
        return False

def write_txt_with_retry(csv_file, txt_file, max_retries=3):
    """尝试转换CSV到TXT文件，包含重试机制"""
    for attempt in range(max_retries):
        try:
            print(f"尝试转换CSV到TXT (第{attempt + 1}次)...")
            if csv_to_txt(csv_file, txt_file):
                print("CSV到TXT转换成功")
                return True
            else:
                raise Exception("转换失败")
        except OSError as e:
            if "Input/output error" in str(e):
                print(f"I/O错误 (尝试 {attempt + 1}/{max_retries}): {e}")
                if attempt < max_retries - 1:
                    print("等待后重试...")
                    time.sleep(2)  # 等待2秒后重试
                    # 尝试同步文件系统
                    sync_filesystem()
                    time.sleep(1)
                else:
                    print("所有重试都失败了")
                    raise
            else:
                raise
        except Exception as e:
            print(f"其他错误: {e}")
            raise
    
    return False

def create_temp_txt_and_copy(csv_file, txt_file):
    """先在本地转换CSV到TXT，然后复制到U盘"""
    import tempfile
    
    try:
        # 创建临时文件
        with tempfile.NamedTemporaryFile(suffix='.txt', delete=False) as temp_file:
            temp_path = temp_file.name
        
        print(f"先在本地转换CSV到TXT: {temp_path}")
        
        # 转换到临时位置
        if not csv_to_txt(csv_file, temp_path):
            raise Exception("CSV到TXT转换失败")
        print("本地TXT创建成功")
        
        # 复制到目标位置
        print(f"复制TXT到U盘: {txt_file}")
        shutil.copy2(temp_path, txt_file)
        print("复制完成")
        
        # 删除临时文件
        os.unlink(temp_path)
        
        return True
        
    except Exception as e:
        print(f"临时文件方案失败: {e}")
        # 清理临时文件
        try:
            if 'temp_path' in locals():
                os.unlink(temp_path)
        except:
            pass
        return False

def sync_filesystem():
    """同步文件系统缓存到磁盘"""
    try:
        os.sync()
        print("Synced filesystem")
    except:
        pass

def validate_txt_file(txt_file):
    """验证TXT文件是否成功创建"""
    if not os.path.exists(txt_file):
        print(f"✗ 错误：TXT文件未创建：{txt_file}")
        return False
    
    file_size = os.path.getsize(txt_file)
    if file_size == 0:
        print(f"✗ 错误：生成的TXT文件大小为0：{txt_file}")
        return False
    
    # 获取文件修改时间
    import stat
    file_stat = os.stat(txt_file)
    mod_time = datetime.fromtimestamp(file_stat.st_mtime)
    
    print(f"✓ 成功创建TXT文件：{txt_file} ({file_size/1024:.1f} KB)")
    print(f"  文件修改时间：{mod_time.strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"  当前系统时间：{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    
    return True

def main():
    parser = argparse.ArgumentParser(description='Convert CSV file to TXT format')
    parser.add_argument('csv_file', nargs='?', default='output.csv',
                       help='Source CSV file to convert (default: output.csv)')
    parser.add_argument('destination', nargs='?', default=None,
                       help='Destination directory (optional, auto-detected if not specified)')
    parser.add_argument('-d', '--dest', 
                       help='Alternative way to specify destination directory')
    parser.add_argument('-o', '--output',
                       help='Output TXT file path (optional, auto-generated if not specified)')
    
    args = parser.parse_args()
    
    csv_file = args.csv_file
    
    # 确定输出文件名的优先级：-o选项 > 自动生成
    if args.output:
        txt_file = args.output
    else:
        # 从CSV文件名生成TXT文件名
        csv_path = Path(csv_file)
        txt_filename = csv_path.stem + '.txt'
        
        # 确定目标目录
        if args.destination:
            dest_directory = args.destination
        elif args.dest:
            dest_directory = args.dest
        else:
            # 自动检测USB设备
            print("正在自动检测USB设备...")
            dest_directory = None
            usb_paths = ["/run/media/sda1", "/run/media/sda2", "/run/media/sda3", "/run/media/sda4"]
            for path in usb_paths:
                if os.path.exists(path):
                    dest_directory = path
                    print(f"检测到USB设备: {dest_directory}")
                    break
            
            if not dest_directory:
                print("错误: 未检测到USB设备，请手动指定目标目录")
                print("使用方法: python ConvertTxt.py source.csv /run/media/sda1")
                return 1
        
        txt_file = os.path.join(dest_directory, txt_filename)
    
    print("CSV to TXT Converter")
    print("=" * 50)
    
    if not os.path.exists(csv_file):
        print(f"Error: {csv_file} not found!")
        return 1
    
    file_size = os.path.getsize(csv_file)
    print(f"Source: {csv_file} ({file_size/1024:.1f} KB)")
    print(f"Target: {txt_file}")
    print()
    
    try:
        start_time = datetime.now()
        print(f"Started at: {start_time.strftime('%Y-%m-%d %H:%M:%S')}")
        
        # 检查是否写入到U盘
        if is_usb_path(txt_file):
            print("检测到U盘路径，使用兼容模式...")
            get_filesystem_info(txt_file)
        
        # 转换文件 - 首先尝试直接转换
        success = False
        try:
            if not write_txt_with_retry(csv_file, txt_file):
                # 如果直接转换失败，尝试临时文件方案
                if is_usb_path(txt_file):
                    print("直接转换失败，尝试临时文件方案...")
                    success = create_temp_txt_and_copy(csv_file, txt_file)
                else:
                    success = False
            else:
                success = True
        except Exception as e:
            print(f"CSV到TXT转换过程中出错: {e}")
            success = False
        
        if not success:
            print("✗ 文件转换失败")
            return 1
        
        # U盘同步处理
        if is_usb_path(txt_file):
            print("同步文件系统到U盘...")
            time.sleep(1.0)
            sync_filesystem()
            time.sleep(0.5)
            
            # 时间戳修改
            try:
                current_time = time.time()
                local_time = datetime.now()
                utc_time = datetime.utcnow()
                time_offset = (local_time - utc_time).total_seconds()
                
                print(f"时区信息: 本地时间={local_time.strftime('%H:%M:%S')}, UTC时间={utc_time.strftime('%H:%M:%S')}, 偏移={time_offset}秒")
                
                adjusted_time = current_time + time_offset
                os.utime(txt_file, (adjusted_time, adjusted_time))
                print(f"✓ 已更新文件时间戳 (本地时间: {local_time.strftime('%H:%M:%S')})")
                
                # 给文件系统更多时间来更新时间戳
                time.sleep(1.0)
                sync_filesystem()
                time.sleep(0.5)
                
            except Exception as e:
                print(f"✗ 无法更新文件时间戳: {e}")
        
        # 最终同步，确保所有更改都写入磁盘
        time.sleep(0.5)
        sync_filesystem()
        
        # 验证转换结果
        if validate_txt_file(txt_file):
            end_time = datetime.now()
            duration = (end_time - start_time).total_seconds()
            
            print(f"Completed at: {end_time.strftime('%Y-%m-%d %H:%M:%S')}")
            print(f"Total time: {duration:.1f} seconds")
            print(f"Output: {txt_file}")
            return 0
        else:
            return 1
            
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        return 1

if __name__ == "__main__":
    exit_code = main()
    exit(exit_code)

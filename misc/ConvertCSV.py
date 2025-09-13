import os
import shutil
import time
from datetime import datetime
import argparse
from pathlib import Path

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

def copy_csv_with_retry(source_file, target_file, max_retries=3):
    """尝试复制CSV文件，包含重试机制"""
    for attempt in range(max_retries):
        try:
            print(f"尝试复制CSV文件 (第{attempt + 1}次)...")
            shutil.copy2(source_file, target_file)
            print("CSV复制成功")
            return True
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

def create_temp_csv_and_copy(source_file, target_file):
    """先在本地创建临时文件，然后复制到U盘"""
    import tempfile
    
    try:
        # 创建临时文件
        with tempfile.NamedTemporaryFile(suffix='.csv', delete=False) as temp_file:
            temp_path = temp_file.name
        
        print(f"先在本地创建临时CSV: {temp_path}")
        
        # 复制到临时位置
        shutil.copy2(source_file, temp_path)
        print("本地临时CSV创建成功")
        
        # 复制到目标位置
        print(f"复制CSV到U盘: {target_file}")
        shutil.copy2(temp_path, target_file)
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

def validate_csv_file(csv_file):
    """验证CSV文件是否成功创建"""
    if not os.path.exists(csv_file):
        print(f"✗ 错误：CSV文件未创建：{csv_file}")
        return False
    
    file_size = os.path.getsize(csv_file)
    if file_size == 0:
        print(f"✗ 错误：生成的CSV文件大小为0：{csv_file}")
        return False
    
    # 获取文件修改时间
    import stat
    file_stat = os.stat(csv_file)
    mod_time = datetime.fromtimestamp(file_stat.st_mtime)
    
    print(f"✓ 成功创建CSV文件：{csv_file} ({file_size/1024:.1f} KB)")
    print(f"  文件修改时间：{mod_time.strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"  当前系统时间：{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    
    return True

def get_target_directory(source_path):
    """从源文件路径生成目标文件名（模拟C++中的GetTargetDirectory）"""
    # 获取文件名（不包含扩展名）
    base_name = Path(source_path).stem
    return base_name

def copy_csv_to_usb(source_file, usb_directory):
    """将CSV文件复制到U盘"""
    
    if not os.path.exists(source_file):
        raise Exception(f"源文件不存在: {source_file}")
    
    start_time = datetime.now()
    print(f"Started at: {start_time.strftime('%Y-%m-%d %H:%M:%S')}")
    
    # 生成目标文件名
    target_name = get_target_directory(source_file) + ".csv"
    target_file = os.path.join(usb_directory, target_name)
    
    print(f"源文件: {source_file}")
    print(f"目标文件: {target_file}")
    
    # 确保目标目录存在
    target_dir = os.path.dirname(target_file)
    if not os.path.exists(target_dir):
        print(f"创建目录: {target_dir}")
        os.makedirs(target_dir, exist_ok=True)
    
    copy_start = datetime.now()
    
    # 检查是否写入到U盘
    if is_usb_path(target_file):
        print("检测到U盘路径，使用兼容模式...")
        get_filesystem_info(target_file)
    
    # 复制文件
    success = False
    
    # 首先尝试直接复制
    try:
        if not copy_csv_with_retry(source_file, target_file):
            # 如果直接复制失败，尝试临时文件方案
            if is_usb_path(target_file):
                print("直接复制失败，尝试临时文件方案...")
                success = create_temp_csv_and_copy(source_file, target_file)
            else:
                success = False
        else:
            success = True
    except Exception as e:
        print(f"CSV复制过程中出错: {e}")
        success = False
    
    if not success:
        raise Exception("CSV文件复制失败，请检查U盘状态或尝试重新插拔U盘")
    
    # U盘需要额外的同步处理（无论哪种复制方式）
    if is_usb_path(target_file):
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
            os.utime(target_file, (adjusted_time, adjusted_time))
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
    
    copy_end = datetime.now()
    end_time = datetime.now()
    
    copy_duration = (copy_end - copy_start).total_seconds()
    total_duration = (end_time - start_time).total_seconds()
    
    print(f"CSV copy took: {copy_duration:.1f} seconds")
    print(f"Completed at: {end_time.strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"Total time: {total_duration:.1f} seconds")
    print(f"Output: {target_file}")

def copy_multiple_csv_files(source_files, usb_directory):
    """复制多个CSV文件到U盘（模拟CSVExportWorker的功能）"""
    total_files = len(source_files)
    success_count = 0
    failed_files = []
    
    print(f"开始复制 {total_files} 个CSV文件到 {usb_directory}")
    
    for i, source_file in enumerate(source_files):
        try:
            print(f"\n处理文件 {i+1}/{total_files}: {source_file}")
            copy_csv_to_usb(source_file, usb_directory)
            success_count += 1
            print(f"进度: {i+1}/{total_files} 完成")
        except Exception as e:
            print(f"✗ 文件复制失败: {source_file}")
            print(f"错误: {e}")
            failed_files.append(source_file)
    
    # 输出总结
    print(f"\n=== 复制完成 ===")
    print(f"成功: {success_count}/{total_files}")
    if failed_files:
        print(f"失败: {len(failed_files)}")
        for failed_file in failed_files:
            print(f"  - {failed_file}")
    
    return success_count == total_files

def main():
    parser = argparse.ArgumentParser(description='Copy CSV file to destination directory')
    parser.add_argument('source_file', nargs='?', default='output.csv',
                       help='Source CSV file to copy (default: output.csv)')
    parser.add_argument('destination', nargs='?', default=None,
                       help='Destination directory (optional, auto-detected if not specified)')
    parser.add_argument('-d', '--dest', 
                       help='Alternative way to specify destination directory')
    
    args = parser.parse_args()
    
    source_file = args.source_file
    
    # 确定目标目录的优先级：命令行第二个参数 > -d选项 > 自动检测
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
            print("使用方法: python ConvertCSV.py source.csv /run/media/sda1")
            return 1
    
    print("CSV File Copy Tool")
    print("=" * 50)
    
    if not os.path.exists(source_file):
        print(f"Error: {source_file} not found!")
        return 1
    
    if not os.path.exists(dest_directory):
        print(f"Error: Destination directory {dest_directory} not found!")
        return 1
    
    file_size = os.path.getsize(source_file)
    print(f"Source: {source_file} ({file_size/1024:.1f} KB)")
    
    # 生成目标文件路径（保持原文件名）
    target_file = os.path.join(dest_directory, os.path.basename(source_file))
    print(f"Target: {target_file}")
    print()
    
    try:
        start_time = datetime.now()
        print(f"Started at: {start_time.strftime('%Y-%m-%d %H:%M:%S')}")
        
        # 简单复制文件
        if is_usb_path(target_file):
            print("检测到U盘路径，使用兼容模式...")
            get_filesystem_info(target_file)
        
        # 复制文件
        if not copy_csv_with_retry(source_file, target_file):
            print("✗ 文件复制失败")
            return 1
        
        # U盘同步处理
        if is_usb_path(target_file):
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
                os.utime(target_file, (adjusted_time, adjusted_time))
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
        
        # 验证复制结果
        if os.path.exists(target_file):
            target_size = os.path.getsize(target_file)
            end_time = datetime.now()
            duration = (end_time - start_time).total_seconds()
            
            print(f"✓ 成功复制文件：{target_file} ({target_size/1024:.1f} KB)")
            print(f"Completed at: {end_time.strftime('%Y-%m-%d %H:%M:%S')}")
            print(f"Total time: {duration:.1f} seconds")
            return 0
        else:
            print("✗ 文件复制失败")
            return 1
            
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        return 1

if __name__ == "__main__":
    exit_code = main()
    exit(exit_code)

import pandas as pd
from reportlab.lib.pagesizes import A3, landscape
from reportlab.platypus import SimpleDocTemplate, Table, TableStyle, PageBreak
from reportlab.lib import colors
from reportlab.lib.units import mm
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
import os
import warnings
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

def write_pdf_with_retry(doc, story, pdf_file, max_retries=3):
    """尝试写入PDF文件，包含重试机制"""
    for attempt in range(max_retries):
        try:
            print(f"尝试写入PDF文件 (第{attempt + 1}次)...")
            doc.build(story)
            print("PDF写入成功")
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

def create_temp_pdf_and_copy(doc, story, pdf_file):
    """先在本地创建PDF，然后复制到U盘"""
    import tempfile
    import shutil
    
    try:
        # 创建临时文件
        with tempfile.NamedTemporaryFile(suffix='.pdf', delete=False) as temp_file:
            temp_path = temp_file.name
        
        print(f"先在本地创建PDF: {temp_path}")
        
        # 使用临时路径创建PDF文档
        temp_doc = SimpleDocTemplate(
            temp_path,
            pagesize=landscape(A3),
            rightMargin=10*mm,
            leftMargin=10*mm,
            topMargin=10*mm,
            bottomMargin=10*mm
        )
        
        # 构建PDF
        temp_doc.build(story)
        print("本地PDF创建成功")
        
        # 复制到目标位置
        print(f"复制PDF到U盘: {pdf_file}")
        shutil.copy2(temp_path, pdf_file)
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
    """同步文件系统缓存到磁盘"""
    try:
        os.sync()
        print("Synced filesystem")
    except:
        pass

def validate_pdf_file(pdf_file):
    """验证PDF文件是否成功创建"""
    if not os.path.exists(pdf_file):
        print(f"✗ 错误：PDF文件未创建：{pdf_file}")
        return False
    
    file_size = os.path.getsize(pdf_file)
    if file_size == 0:
        print(f"✗ 错误：生成的PDF文件大小为0：{pdf_file}")
        return False
    
    # 获取文件修改时间
    import stat
    file_stat = os.stat(pdf_file)
    mod_time = datetime.fromtimestamp(file_stat.st_mtime)
    
    print(f"✓ 成功创建PDF文件：{pdf_file} ({file_size/1024:.1f} KB)")
    print(f"  文件修改时间：{mod_time.strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"  当前系统时间：{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    
    return True

def register_chinese_font():
    """注册中文字体"""
    font_paths = [
        "/usr/share/fonts/wqy-zenhei.ttf",
        "/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc"
        # Windows 常见路径
        "C:/Windows/Fonts/simsun.ttc",      # 宋体
        "C:/Windows/Fonts/simhei.ttf",      # 黑体
        "C:/Windows/Fonts/msyh.ttc",        # 微软雅黑
        "C:/Windows/Fonts/msyh.ttf",        # 微软雅黑（部分系统）
    ]
    
    for font_path in font_paths:
        if os.path.exists(font_path):
            try:
                pdfmetrics.registerFont(TTFont('WQYZenHei', font_path))
                print("WQYZenHei font registered successfully")
                return 'WQYZenHei'
            except Exception as e:
                print(f"Failed to register font: {e}")
                continue
    
    print("Using default font")
    return 'Helvetica'

def load_csv_data(csv_file):
    """加载CSV数据"""
    print(f"Loading CSV file: {csv_file}")
    
    try:
        df = pd.read_csv(csv_file, encoding='utf-8-sig')
        print(f"CSV loaded: {df.shape[0]} rows × {df.shape[1]} columns")
        return df
    except Exception as e:
        print(f"Failed to load CSV: {e}")
        return None

def clean_text(text, max_length=15):
    """清理文本"""
    if pd.isna(text):
        return ''
    
    text = str(text)[:max_length]
    # 移除问题字符
    return ''.join(c for c in text if ord(c) < 65536)

def csv_to_pdf_reportlab(csv_file, pdf_file):
    """使用reportlab将CSV转换为PDF"""
    
    # 加载数据
    df = load_csv_data(csv_file)
    if df is None:
        raise Exception("Failed to load CSV file")
    
    start_time = datetime.now()
    print(f"Started at: {start_time.strftime('%Y-%m-%d %H:%M:%S')}")
    
    # 注册中文字体
    font_name = register_chinese_font()
    
    # 创建PDF文档
    doc = SimpleDocTemplate(
        pdf_file,
        pagesize=landscape(A3),
        rightMargin=10*mm,
        leftMargin=10*mm,
        topMargin=10*mm,
        bottomMargin=10*mm
    )
    
    print("Preprocessing data...")
    
    # 准备表格数据
    table_data = []
    
    # 添加表头
    headers = [clean_text(col, 20) for col in df.columns]
    table_data.append(headers)
    
    # 添加数据行
    total_rows = len(df)
    for idx, (_, row) in enumerate(df.iterrows()):
        # if idx % 1000 == 0:
        #     print(f"Processing: {idx + 1}/{total_rows}")
        
        row_data = [clean_text(cell, 15) for cell in row]
        table_data.append(row_data)
    
    print("Creating PDF table...")
    
    # 设置列宽
    col_widths = [40*mm, 40*mm, 40*mm, 40*mm] + [20*mm] * 10
    num_columns = len(df.columns)
    if len(col_widths) < num_columns:
        col_widths = (col_widths * ((num_columns // len(col_widths)) + 1))[:num_columns]
    else:
        col_widths = col_widths[:num_columns]
    
    # 分批处理数据以避免内存问题
    batch_size = 1000
    story = []
    
    for batch_start in range(0, len(table_data), batch_size):
        batch_end = min(batch_start + batch_size, len(table_data))
        
        if batch_start == 0:
            # 第一批包含表头
            batch_data = table_data[batch_start:batch_end]
        else:
            # 后续批次重新添加表头
            batch_data = [headers] + table_data[batch_start:batch_end]
        
        # print(f"Creating batch {batch_start//batch_size + 1}: rows {batch_start}-{batch_end-1}")
        
        # 创建表格
        table = Table(batch_data, colWidths=col_widths, repeatRows=1)
        
        # 设置表格样式
        table.setStyle(TableStyle([
            ('BACKGROUND', (0, 0), (-1, 0), colors.grey),
            ('TEXTCOLOR', (0, 0), (-1, 0), colors.whitesmoke),
            ('ALIGN', (0, 0), (-1, -1), 'LEFT'),
            ('FONTNAME', (0, 0), (-1, -1), font_name),
            ('FONTSIZE', (0, 0), (-1, -1), 8),
            ('ROWBACKGROUNDS', (0, 1), (-1, -1), [colors.beige, colors.white]),
            ('GRID', (0, 0), (-1, -1), 0.5, colors.black),
        ]))
        
        story.append(table)
        
        # 除了最后一批，都添加分页符
        if batch_end < len(table_data):
            story.append(PageBreak())
    
    print("Building PDF...")
    output_start = datetime.now()
    
    # 检查是否写入到U盘
    if is_usb_path(pdf_file):
        print("检测到U盘路径，使用兼容模式...")
        get_filesystem_info(pdf_file)
    
    # 生成PDF
    success = False
    
    # 首先尝试直接写入
    try:
        if not write_pdf_with_retry(doc, story, pdf_file):
            # 如果直接写入失败，尝试临时文件方案
            if is_usb_path(pdf_file):
                print("直接写入失败，尝试临时文件方案...")
                success = create_temp_pdf_and_copy(doc, story, pdf_file)
            else:
                success = False
        else:
            success = True
    except Exception as e:
        print(f"PDF写入过程中出错: {e}")
        success = False
    
    if not success:
        raise Exception("PDF文件写入失败，请检查U盘状态或尝试重新插拔U盘")
    
    # U盘需要额外的同步处理（无论哪种写入方式）
    if is_usb_path(pdf_file):
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
            os.utime(pdf_file, (adjusted_time, adjusted_time))
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
    
    output_end = datetime.now()
    end_time = datetime.now()
    
    output_duration = (output_end - output_start).total_seconds()
    total_duration = (end_time - start_time).total_seconds()
    
    print(f"PDF generation took: {output_duration:.1f} seconds")
    print(f"Completed at: {end_time.strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"Total time: {total_duration:.1f} seconds")
    print(f"Output: {pdf_file}")

def main():
    parser = argparse.ArgumentParser(description='Convert CSV to PDF using ReportLab')
    parser.add_argument('csv_file', nargs='?', default='output.csv', 
                       help='Input CSV file path (default: output.csv)')
    parser.add_argument('pdf_file', nargs='?', default=None,
                       help='Output PDF file path (optional, auto-generated if not specified)')
    parser.add_argument('-o', '--output', 
                       help='Alternative way to specify output PDF file path')
    
    args = parser.parse_args()
    
    csv_file = args.csv_file
    
    # 确定输出文件名的优先级：命令行第二个参数 > -o选项 > 自动生成
    if args.pdf_file:
        pdf_file = args.pdf_file
    elif args.output:
        pdf_file = args.output
    else:
        # 从CSV文件名生成PDF文件名
        csv_path = Path(csv_file)
        pdf_file = csv_path.with_suffix('.pdf').name
         
    print("ReportLab CSV to PDF Converter")
    print("=" * 50)
    
    if not os.path.exists(csv_file):
        print(f"Error: {csv_file} not found!")
        return 1
    
    file_size = os.path.getsize(csv_file)
    print(f"File: {csv_file} ({file_size/1024:.1f} KB)")
    print()
    
    try:
        csv_to_pdf_reportlab(csv_file, pdf_file)
        
        # 验证PDF文件
        if validate_pdf_file(pdf_file):
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

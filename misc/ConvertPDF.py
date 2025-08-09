import pandas as pd
from reportlab.lib.pagesizes import A3, landscape
from reportlab.platypus import SimpleDocTemplate, Table, TableStyle, PageBreak
from reportlab.lib import colors
from reportlab.lib.units import mm
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
import os
import warnings
from datetime import datetime
import argparse
from pathlib import Path

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
    
    # 生成PDF
    doc.build(story)
    
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
        return
    
    file_size = os.path.getsize(csv_file)
    print(f"File: {csv_file} ({file_size/1024:.1f} KB)")
    print()
    
    try:
        csv_to_pdf_reportlab(csv_file, pdf_file)
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    main()

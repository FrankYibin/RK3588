"""
ReportLab CSV to PDF Converter - 简化版

首先需要安装ReportLab:
pip install reportlab

然后运行此脚本
"""

import pandas as pd
from reportlab.platypus import SimpleDocTemplate, Table, TableStyle
from reportlab.lib.pagesizes import A3, landscape
from reportlab.lib import colors
from reportlab.lib.units import mm
import os
from datetime import datetime

def csv_to_pdf_simple(csv_file, pdf_file):
    """简化的ReportLab转换"""
    
    print(f"Loading {csv_file}...")
    df = pd.read_csv(csv_file, encoding='utf-8-sig')
    print(f"Loaded: {df.shape[0]} rows × {df.shape[1]} columns")
    
    start_time = datetime.now()
    
    # 创建PDF
    doc = SimpleDocTemplate(pdf_file, pagesize=landscape(A3))
    
    # 准备数据 - 限制文本长度以提高性能
    print("Preparing data...")
    data = []
    
    # 表头
    headers = [str(col)[:15] for col in df.columns]
    data.append(headers)
    
    # 数据行
    for idx, row in df.iterrows():
        if idx % 1000 == 0:
            print(f"Processing: {idx + 1}/{len(df)}")
        
        row_data = [str(cell)[:12] if not pd.isna(cell) else '' for cell in row]
        data.append(row_data)
    
    print("Creating table...")
    
    # 创建表格
    table = Table(data)
    
    # 简单样式
    table.setStyle(TableStyle([
        ('BACKGROUND', (0, 0), (-1, 0), colors.grey),
        ('TEXTCOLOR', (0, 0), (-1, 0), colors.whitesmoke),
        ('ALIGN', (0, 0), (-1, -1), 'LEFT'),
        ('FONTSIZE', (0, 0), (-1, -1), 7),
        ('ROWBACKGROUNDS', (0, 1), (-1, -1), [colors.beige, colors.white]),
    ]))
    
    print("Building PDF...")
    output_start = datetime.now()
    
    # 生成PDF
    doc.build([table])
    
    end_time = datetime.now()
    total_time = (end_time - start_time).total_seconds()
    output_time = (end_time - output_start).total_seconds()
    
    print(f"PDF generation: {output_time:.1f}s")
    print(f"Total time: {total_time:.1f}s")
    print(f"Output: {pdf_file}")

if __name__ == "__main__":
    csv_file = "output.csv"
    pdf_file = "output_reportlab_simple.pdf"
    
    print("Simple ReportLab Converter")
    print("=" * 40)
    
    if not os.path.exists(csv_file):
        print(f"Error: {csv_file} not found!")
    else:
        try:
            csv_to_pdf_simple(csv_file, pdf_file)
        except ImportError:
            print("ReportLab not installed. Install with: pip install reportlab")
        except Exception as e:
            print(f"Error: {e}")

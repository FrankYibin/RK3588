import pandas as pd
from fpdf import FPDF
import os
import warnings
from datetime import datetime
from multiprocessing import Pool, cpu_count
import io

# 禁用FPDF的字体警告
warnings.filterwarnings('ignore', message='cmap value too big/small.*')

class PDF(FPDF):
    def __init__(self, orientation='L', unit='mm', format='A3'):
        super().__init__(orientation, unit, format)
        self.current_font_name = "Arial"  # 默认字体
        self._load_chinese_font()
        
    def _load_chinese_font(self):
        """加载WQYZenHei中文字体"""
        # 只使用WQYZenHei字体
        font_paths = [
            "/usr/share/fonts/wqy-zenhei.ttf",
            "/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc"
        ]
        
        for font_path in font_paths:
            if os.path.exists(font_path):
                try:
                    self.add_font("WQYZenHei", style="", fname=font_path, uni=True)
                    self.current_font_name = "WQYZenHei"
                    self.set_font("WQYZenHei", size=10)
                    print("WQYZenHei font loaded successfully")
                    return
                except Exception as font_error:
                    print(f"Failed to load WQYZenHei: {font_error}")
                    continue
        
        # 如果没有找到WQYZenHei字体，使用默认字体
        print("WQYZenHei font not found, using Arial")
        print("To install: sudo apt-get install fonts-wqy-zenhei")
        self.set_font("Arial", size=10)
        self.current_font_name = "Arial"

def load_csv_data(csv_file):
    """加载CSV数据，使用UTF-8-SIG编码"""
    print(f"Loading CSV file: {csv_file}")
    
    try:
        print("Loading with UTF-8-SIG encoding...")
        df = pd.read_csv(csv_file, encoding='utf-8-sig')
        print("CSV loaded successfully with UTF-8-SIG encoding")
        print(f"Data shape: {df.shape[0]} rows × {df.shape[1]} columns")
        
        return df
    except Exception as e:
        print(f"Failed to load CSV: {type(e).__name__}: {e}")
        return None

def csv_to_pdf(csv_file, pdf_file):
    """将CSV转换为PDF"""
    # 加载数据
    df = load_csv_data(csv_file)
    if df is None:
        raise Exception("Failed to load CSV file")
    
    # 创建PDF
    pdf = PDF(orientation='L')
    pdf.add_page()
    
    print(f"Using font: {pdf.current_font_name}")
    
    # Set column widths and headers
    col_widths = [40, 40, 40, 40, 20, 20, 20, 20, 20, 20, 20, 20, 20, 40] * len(df.columns)  # Adjust widths based on column count
    headers = list(df.columns)
    
    # Ensure we have enough widths for all columns
    num_columns = len(df.columns)
    if len(col_widths) < num_columns:
        # If not enough widths defined, repeat the pattern or use default width
        col_widths = (col_widths * ((num_columns // len(col_widths)) + 1))[:num_columns]
    else:
        # Use only the number of widths we need
        col_widths = col_widths[:num_columns]
    
    print(f"Using custom column widths for {num_columns} columns: {col_widths}")
    
    try:
        # 设置字体
        pdf.set_font(pdf.current_font_name, size=10)
        
        # 记录开始时间
        start_time = datetime.now()
        print(f"Started processing at: {start_time.strftime('%Y-%m-%d %H:%M:%S')}")
        
        # 预处理数据 - 一次性清理所有文本，避免在循环中重复处理
        print("Preprocessing data...")
        processed_data = []
        
        for col_idx, col in enumerate(df.columns):
            # 处理表头
            if pd.isna(col):
                header_text = ''
            else:
                header_text = str(col)[:20]
                header_text = ''.join(c for c in header_text if ord(c) < 65536)
            processed_data.append(header_text)
        
        # 预处理所有数据行
        all_rows_data = []
        for row_idx in range(len(df)):
            row_data = []
            for cell_value in df.iloc[row_idx]:
                if pd.isna(cell_value):
                    text = ''
                else:
                    text = str(cell_value)[:15]
                    # 批量字符过滤
                    if any(ord(c) >= 65536 for c in text):
                        text = ''.join(c for c in text if ord(c) < 65536)
                row_data.append(text)
            all_rows_data.append(row_data)
        
        print("Data preprocessing completed. Starting PDF generation...")
        
        # 写入表头 - 移除边框以提高性能
        for i, header_text in enumerate(processed_data):
            pdf.cell(col_widths[i], 10, header_text, border=0)
        pdf.ln()
        
        # 写入数据行 - 使用预处理的数据
        total_rows = len(all_rows_data)
        
        # 预先设置字体，避免重复设置
        pdf.set_font(pdf.current_font_name, size=10)
        
        print(f"Writing {total_rows} rows to PDF...")
        
        # 优化：增加每页行数，减少总页数
        rows_per_page = 200  # 增加到200行每页，减少页数
        current_row_on_page = 0
        
        for row_idx, row_data in enumerate(all_rows_data):
            if row_idx % 1000 == 0:
                print(f"Writing: {row_idx + 1}/{total_rows}")
            
            # 检查是否需要新页
            if current_row_on_page >= rows_per_page:
                pdf.add_page()
                pdf.set_font(pdf.current_font_name, size=10)
                current_row_on_page = 0
                # 不重复写入表头，减少内容复杂度
            
            for i, text in enumerate(row_data):
                pdf.cell(col_widths[i], 10, text, border=0)  # 移除边框
            pdf.ln()
            current_row_on_page += 1
        
        # 保存PDF - 最激进的优化：分块输出
        print("Generating PDF file...")
        output_start = datetime.now()
        
        # 设置FPDF压缩选项以提高输出速度
        pdf.set_compression(False)  # 禁用压缩以提高速度
        
        # 直接输出，不使用内存缓冲（减少内存开销）
        pdf.output(pdf_file)
        
        output_end = datetime.now()
        output_duration = output_end - output_start
        print(f"PDF output took: {output_duration.total_seconds():.1f} seconds")
        
        # 记录结束时间和计算耗时
        end_time = datetime.now()
        duration = end_time - start_time
        print(f"Completed at: {end_time.strftime('%Y-%m-%d %H:%M:%S')}")
        print(f"Total processing time: {duration.total_seconds():.1f} seconds")
        print(f"Output file: {pdf_file}")
        
    except Exception as e:
        print(f"Error: {e}")
        raise

def main():
    """主函数"""
    csv_file = "output.csv"
    pdf_file = "output.pdf"
    
    print("CSV to PDF Converter Starting...")
    print("=" * 50)
    
    # 检查文件是否存在
    if not os.path.exists(csv_file):
        print(f"Error: CSV file '{csv_file}' not found!")
        return
    
    # 显示文件信息
    file_size = os.path.getsize(csv_file)
    print(f"File: {csv_file}")
    print(f"Size: {file_size:,} bytes ({file_size/1024:.1f} KB)")
    print()
    
    # 转换CSV到PDF
    try:
        print("CSV to PDF Conversion:")
        print("-" * 30)
        csv_to_pdf(csv_file, pdf_file)
    except Exception as e:
        print(f"Conversion failed: {e}")
        print("Please check if the CSV file is readable and contains valid data.")
    
    print("\nProcess completed!")

if __name__ == "__main__":
    main()

import pandas as pd
from fpdf import FPDF

class PDF(FPDF):
    def __init__(self, orientation='L', unit='mm', format='A3'):
        super().__init__(orientation, unit, format)  # 确保传递参数
        self.add_font("SimSun", style="", fname="simsun.ttc", uni=True)
        # self.add_font("NotoSansSC", "", "NotoSansSC-Regular.ttf", uni=True)
        self.set_font("SimSun", size=10)

def csv_to_pdf(csv_file, pdf_file):
    # Read the CSV file
    df = pd.read_csv(csv_file, encoding='utf-8')
    # df = pd.read_csv(csv_file, encoding='gbk')  # 尝试GBK编码
    print(f"columns: {df.columns}")

    # Initialize PDF
    pdf = PDF(orientation='L')  # 横向页面模式
    pdf.add_page()

    # Set column widths and headers
    col_widths = [40, 40, 40, 40, 20, 20, 20, 20, 20, 20, 20, 20, 20, 40] * len(df.columns)  # Adjust widths based on column count
    headers = list(df.columns)

    # Write header row
    for header in headers:
        pdf.cell(col_widths[headers.index(header)], 10, header, border=1)
    pdf.ln()
    
    # Write data rows
    for _, row in df.iterrows():
        for i, cell in enumerate(row):
            pdf.cell(col_widths[i], 10, str(cell), border=1)
        pdf.ln()
    
    # Save PDF
    pdf.output(pdf_file)
    print(f"PDF saved to: {pdf_file}")

# Usage example
csv_file = "output.csv"
pdf_file = "output.pdf"
csv_to_pdf(csv_file, pdf_file)

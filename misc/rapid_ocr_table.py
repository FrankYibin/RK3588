# rapid_ocr_table.py
from rapidocr_onnxruntime import RapidOCR
import sys
import cv2
import numpy as np

def sort_text_lines(result, y_threshold=10):
    """
    将 OCR 结果按行（Y 坐标）分组，再按 X 排序
    """
    if not result:
        return []

    boxes, texts, _ = list(zip(*result))

    # 计算每个框的中心 Y 坐标
    center_ys = [np.mean([box[0][1], box[1][1], box[2][1], box[3][1]]) for box in boxes]
    
    # 按 Y 分组为“行”
    lines = []
    current_line = []
    current_y = center_ys[0]

    combined = sorted(zip(center_ys, boxes, texts), key=lambda x: x[0])

    for cy, box, text in combined:
        if abs(cy - current_y) < y_threshold:
            current_line.append((box, text))
        else:
            # 新的一行
            current_line.sort(key=lambda x: x[0][0][0])  # 按 X 排序
            lines.append(current_line)
            current_line = [(box, text)]
            current_y = cy

    if current_line:
        current_line.sort(key=lambda x: x[0][0][0])
        lines.append(current_line)

    return lines

def main():
    if len(sys.argv) < 2:
        print("用法: python rapid_ocr_table.py <图片路径>")
        sys.exit(1)

    image_path = sys.argv[1]

    # 初始化 OCR
    ocr = RapidOCR(use_cuda=False)  # 树莓派无 CUDA

    print("✅ 开始 OCR 识别...")
    result, _ = ocr(image_path)  # 返回 (boxes, txts, scores)

    if not result:
        print("❌ 未识别到任何文本")
        sys.exit(1)

    print(f"✅ 识别到 {len(result)} 个文本块")

    # 按行分组
    lines = sort_text_lines(result, y_threshold=15)

    print("\n" + "="*60)
    print("📄 重建的表格结构（基于坐标）:")
    print("="*60)

    table_data = []
    for i, line in enumerate(lines):
        row = [txt for _, txt in line]
        table_data.append(row)
        print(f"第 {i+1} 行: {' | '.join(row)}")

    # 保存为 CSV（可选）
    import csv
    with open("ocr_output.csv", "w", encoding="utf-8", newline="") as f:
        writer = csv.writer(f)
        writer.writerows(table_data)

    print("="*60)
    print("✅ 文本已保存为 ocr_output.csv")

if __name__ == '__main__':
    main()


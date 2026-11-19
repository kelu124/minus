# Build the datasheet: figures + values come from docs/bench/2026-11-19-datasheet/analyze.py
all: minus-datasheet.pdf
figures values.tex noise_rows.tex:
	cd .. && /usr/bin/python3 docs/bench/2026-11-19-datasheet/analyze.py
minus-datasheet.pdf: minus-datasheet.tex values.tex noise_rows.tex
	pdflatex -interaction=nonstopmode -halt-on-error minus-datasheet.tex >/dev/null
	pdflatex -interaction=nonstopmode -halt-on-error minus-datasheet.tex >/dev/null
	pdflatex -interaction=nonstopmode -halt-on-error minus-datasheet.tex | grep -E "Output written|Error" || true
clean:
	rm -f *.aux *.log *.out *.toc
.PHONY: all clean figures

.PHONY: clean doc-preview doc-spell export

clean:
	rm -rf build tags

doc-preview: build/doc/informe.pdf
	evince build/doc/informe.pdf &

doc-spell: docs/informe.tex
	aspell -t check docs/informe.tex -d es

export: build/doc/informe.pdf
	tar -czvf build/entrega.tar.gz makefile -C build/doc/ informe.pdf

build:
	mkdir build

build/doc: build
	mkdir build/doc

build/doc/informe.pdf: build/doc docs/informe.tex
	pdflatex --output-directory build/doc docs/informe.tex
	pdflatex --output-directory build/doc docs/informe.tex
	pdflatex --output-directory build/doc docs/informe.tex


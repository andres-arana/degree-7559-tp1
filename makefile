build:
	mkdir build

build/doc: build
	mkdir build/doc

clean:
	rm -rf build tags

build/doc/informe.pdf: build/doc docs/informe.tex
	pandoc README.md -o build/doc/README.pdf
	pdflatex --output-directory build/doc docs/informe.tex
	pdflatex --output-directory build/doc docs/informe.tex
	pdflatex --output-directory build/doc docs/informe.tex

doc-preview: build/doc/informe.pdf
	evince build/doc/informe.pdf &

doc-spell: docs/informe.tex
	aspell -t check docs/informe.tex -d es

export: build/doc/informe.pdf
	tar -czvf build/entrega_tp1.tar.gz makefile source1 data -C build/doc/ informe.pdf README.pdf

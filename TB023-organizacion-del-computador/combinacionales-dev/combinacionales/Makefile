MASTER=TallerLogica-Combinatorios-individual.circ
TRUTH=salida_catedra.txt
OUTPUT=output-entrega.txt
RUN_TEST=logisim-evolution --toplevel-circuit "verificador" -tty table

.PHONY: comparar clean all
all: clean $(OUTPUT) comparar

$(OUTPUT): $(MASTER)
	@echo "RUN_TEST: $(RUN_TEST)"
	@echo "OUTPUT: $(OUTPUT)"
	@$(RUN_TEST) $< > $@
	@if [ ! -f $(OUTPUT) ]; then \
		echo "ERROR: No se pudo generar el archivo de salida"; \
	fi

comparar: $(OUTPUT)
	@if diff -q $(TRUTH) $<; then \
    	echo "Las salidas coinciden"; \
	else \
    	echo "ERROR: Las salidas no coinciden"; \
    	diff -y --suppress-common-lines $(TRUTH) $<; \
	fi

clean:
	@echo "Borrando $(OUTPUT) para generar uno nuevo"
	@rm -rf $(OUTPUT)
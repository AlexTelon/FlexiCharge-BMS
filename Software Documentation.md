**About this document**
--------

- This document will contain all of the documentation for all software written towards the BMS.
- Each developer is required to add to this document in order for their software to be considered done.
- Markdown syntax should be used on headings.

**Basic guidelines on how to format your documentation**
--------

- Add a heading at the start of your documentation.
- List the files you have created.
- If your software is dependent on one or more peripherals, list the dependencies and relevant settings.
- Write helpful comments.

**Software for reading the voltage level of a single cell**
--------

This software is made up of two files, "bms_cell_voltage_reader.c" and "bms_cell_voltage_reader.h".
It uses the Analog to Digital Converter (ADC) to measure the analog voltage of a battery cell. The ADC needs to be configured to have a Sampling Time of 480 clock cycles. This analog value is later converted to an integer representation of a floating point number representing a voltage level. A value of 1000 should be interpreted as 1.000V, 970 should be interpreted as 0.970V.

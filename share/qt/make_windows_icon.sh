#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/wayawolfcoin.ico

convert ../../src/qt/res/icons/wayawolfcoin-16.png ../../src/qt/res/icons/wayawolfcoin-32.png ../../src/qt/res/icons/wayawolfcoin-48.png ${ICON_DST}

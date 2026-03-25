#pragma once
#include <vector>
#include "Symbol.h"

class Frame {
    private:
        std::vector<Symbol> _symbols;
        Frame(const std::vector<Symbol>& symbols) : _symbols(symbols) {};
    
    public: 
        static Frame from(const std::vector<Symbol>& symbols) {
            return Frame(symbols);
        }

        void add(const Symbol& symbol) {
            _symbols.push_back(symbol);
        }

        void addSymbols(std::vector<Symbol> symbols) {
            _symbols.insert(_symbols.end(), symbols.begin(), symbols.end());
        }

        const std::vector<Symbol>& getSymbols() const {
            return _symbols;
        }
};
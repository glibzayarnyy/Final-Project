// Name: Glib Zayarnyy
// Seneca Student ID: 102086170
// Seneca email: gzayarnyy@myseneca.ca
// Date of completion: December 2nd, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include "Item.h"
#include "Utilities.h"
#include <iomanip>

unsigned int Item::m_widthField = 1;

// constructor
Item::Item(const std::string& str) {
    Utilities util;
    bool more = true;
    size_t next_pos = 0u;

    m_name = util.extractToken(str, next_pos, more);
    m_serialNumber = std::stoi(util.extractToken(str, next_pos, more));
    m_quantity = std::stoi(util.extractToken(str, next_pos, more));
    m_widthField = util.getFieldWidth();
    m_description = util.extractToken(str, next_pos, more);
}
const std::string& Item::getName() const {
    return m_name;
}

const unsigned int Item::getQuantity() {
    return m_quantity;
}

const unsigned int Item::getSerialNumber() {
    return m_serialNumber++;
}

void Item::updateQuantity() {
    if (m_quantity > 0)
        --m_quantity;
}

void Item::display(std::ostream& os, bool full) const {
    os << std::setw(m_widthField) << std::left << m_name << " [" 
       << std::setw(6) << std::right << std::setfill('0') << m_serialNumber << std::setfill(' ') << "]";
    if (full) {
        os << " Quantity: " << std::setw(m_widthField) << std::left << m_quantity << " Description: " << m_description;
    }
    os << std::endl;
}
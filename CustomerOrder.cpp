// Name: Glib Zayarnyy
// Seneca Student ID: 102086170
// Seneca email: gzayarnyy@myseneca.ca
// Date of completion: December 2nd, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <iostream>
#include <string>
#include <iomanip>
#include "CustomerOrder.h"
#include "Item.h"
#include "Utilities.h"

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() {
    m_cntItem = 0u;
    m_listItem = nullptr;
}


CustomerOrder::CustomerOrder(const std::string& str) {
    
    Utilities util;
    bool more = true;
    size_t next_pos = 0u;
    
    m_name = util.extractToken(str, next_pos, more);
    m_product = util.extractToken(str, next_pos, more);
    m_cntItem = 0u;

    // start_pos is where the list of products begins
    size_t start_pos = next_pos;
    
    while (more) {
        util.extractToken(str, next_pos, more);
        ++m_cntItem;
    }

    m_listItem = new ItemInfo*[m_cntItem];
    
    more = true; 
   
    for (size_t i = 0u; i < m_cntItem; ++i) {
        m_listItem[i] = new ItemInfo(util.extractToken(str, start_pos, more));
    }

    if (util.getFieldWidth() > m_widthField)
        m_widthField = util.getFieldWidth();

}
CustomerOrder::CustomerOrder(CustomerOrder&) {
    throw std::string("Cannot make copies.");
}

CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
    m_listItem = nullptr;
    *this = std::move(src);
}
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) {
    if (&src != this) {
        this->m_name = src.m_name;
        this->m_product = src.m_product;
        if (m_listItem)
            for (unsigned int i = 0; i < m_cntItem; i++)
                delete this->m_listItem[i];
        delete [] this->m_listItem;
        
        this->m_cntItem = src.m_cntItem;
        this->m_listItem = src.m_listItem;

        src.m_listItem = nullptr;
    }

    return *this;
}

CustomerOrder::~CustomerOrder() {
    if (m_listItem)
        for (unsigned int i = 0; i < m_cntItem; ++i)
            delete m_listItem[i];
    delete [] m_listItem;
}

bool CustomerOrder::getItemFillState(std::string str) const {
    bool filled = true;
    for (unsigned int i = 0; i < m_cntItem; ++i) {
        if (m_listItem[i]->m_itemName == str)
            if (!m_listItem[i]->m_fillState) {
                filled = false;
                break;
            }
    }

    return filled;
}

bool CustomerOrder::getOrderFillState() const {
    for (unsigned int i = 0; i < m_cntItem; ++i) {
        if (!m_listItem[i]->m_fillState)
            return false;
    }

    return true;
}

void CustomerOrder::fillItem(Item& item, std::ostream& os) {
    for (unsigned int i = 0; i < m_cntItem; ++i) {

        if (m_listItem[i]->m_itemName == item.getName() && !m_listItem[i]->m_fillState) {
            if (item.getQuantity() > 0) {
                m_listItem[i]->m_serialNumber = item.getSerialNumber();
                item.updateQuantity();
                m_listItem[i]->m_fillState = true;
                os << "Filled ";
            } else {
                os << "Unable to fill ";
            }
            
            os << m_name << ", " << m_product << "[" << m_listItem[i]->m_itemName << "]" << std::endl;
            return;
        }
    }
}

void CustomerOrder::display(std::ostream& os) const {
    os << m_name << " - " << m_product << std::endl;
    for (unsigned int i = 0; i < m_cntItem; i++) {
        os << "[" << std::setw(6) << std::setfill('0') << std::right << m_listItem[i]->m_serialNumber 
           << std::setfill(' ') << "] " << std::setw(m_widthField) << std::left << m_listItem[i]->m_itemName
           << " - " << (m_listItem[i]->m_fillState ? "FILLED" : "MISSING") << std::endl;
    }
}
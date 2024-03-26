//   Ordt 170915.01 autogenerated file 
//   Input: test.rdl
//   Parms: test.parms
//   Date: Tue Mar 26 02:02:59 UTC 2024
//

#include "ordt_pio_common.hpp"
#include "ordt_pio.hpp"

// ------------------ ordt_addr_elem methods ------------------

ordt_addr_elem::ordt_addr_elem(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : m_startaddress(_m_startaddress),
    m_endaddress(_m_endaddress) {
}

bool  ordt_addr_elem::containsAddress(const uint64_t &addr) {
  return ((addr >= m_startaddress) && (addr <= m_endaddress));
}

bool  ordt_addr_elem::isBelowAddress(const uint64_t &addr) {
  return (addr > m_endaddress);
}

bool  ordt_addr_elem::isAboveAddress(const uint64_t &addr) {
  return (addr < m_startaddress);
}

bool  ordt_addr_elem::hasStartAddress(const uint64_t &addr) {
  return (addr == m_startaddress);
}

void  ordt_addr_elem::update_child_ptrs() {
}

// ------------------ ordt_regset methods ------------------

ordt_addr_elem*  ordt_regset::findAddrElem(const uint64_t &addr) {
  int lo = 0;
  int hi = m_children.size()-1;
  int mid = 0;
  while (lo <= hi) {
     mid = (lo + hi) / 2;
     if (m_children[mid]->containsAddress(addr)) {
        //outElem = m_children[mid];
        return m_children[mid];
     }
     else if (m_children[mid]->isAboveAddress(addr))
        hi = mid - 1;
     else
        lo = mid + 1;
  }
  return nullptr;
}

ordt_regset::ordt_regset(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_addr_elem(_m_startaddress, _m_endaddress) {
}

int  ordt_regset::write(const uint64_t &addr, const ordt_data &wdata) {
     if (this->containsAddress(addr)) {
        childElem = this->findAddrElem(addr);
        if (childElem != nullptr) { return childElem->write(addr, wdata); }
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in regset\n";
  #endif
     return 8;
}

int  ordt_regset::read(const uint64_t &addr, ordt_data &rdata) {
     if (this->containsAddress(addr)) {
        childElem = this->findAddrElem(addr);
        if (childElem != nullptr) { return childElem->read(addr, rdata); }
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in regset\n";
  #endif
     rdata.clear();
     return 8;
}

// ------------------ ordt_reg methods ------------------

ordt_reg::ordt_reg(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_addr_elem(_m_startaddress, _m_endaddress) {
}

ordt_reg::ordt_reg(const ordt_reg &_old)
  : ordt_addr_elem(_old),
    m_mutex() {
}

void  ordt_reg::write(const ordt_data &wdata) {
}

int  ordt_reg::write(const uint64_t &addr, const ordt_data &wdata) {
     return 0;
}

void  ordt_reg::read(ordt_data &rdata) {
}

int  ordt_reg::read(const uint64_t &addr, ordt_data &rdata) {
     return 0;
}

// ------------------ ordt_rg_stats_disable_check methods ------------------

ordt_rg_stats_disable_check::ordt_rg_stats_disable_check(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    timer_sram(0, 1, 0x0, r_std, w_std),
    cbuf_fifo(1, 1, 0x0, r_std, w_std),
    lut_st(2, 1, 0x0, r_std, w_std),
    l0_b0(3, 1, 0x0, r_std, w_std),
    l0_b1(4, 1, 0x0, r_std, w_std),
    l0_b2(5, 1, 0x0, r_std, w_std),
    l0_b3(6, 1, 0x0, r_std, w_std) {
}

int  ordt_rg_stats_disable_check::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_stats_disable_check at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_stats_disable_check\n";
  #endif
     return 8;
}

void  ordt_rg_stats_disable_check::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  timer_sram.write(wdata);
  cbuf_fifo.write(wdata);
  lut_st.write(wdata);
  l0_b0.write(wdata);
  l0_b1.write(wdata);
  l0_b2.write(wdata);
  l0_b3.write(wdata);
}

int  ordt_rg_stats_disable_check::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_stats_disable_check at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_stats_disable_check\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_stats_disable_check::read(ordt_data &rdata) {
  rdata.clear();
  for (int widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  timer_sram.read(rdata);
  cbuf_fifo.read(rdata);
  lut_st.read(rdata);
  l0_b0.read(rdata);
  l0_b1.read(rdata);
  l0_b2.read(rdata);
  l0_b3.read(rdata);
}

// ------------------ ordt_rg_stats_features methods ------------------

ordt_rg_stats_features::ordt_rg_stats_features(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    adr_logged(0, 1, 0x1, r_std, w_none),
    correctable(1, 1, 0x0, r_std, w_none),
    checker(2, 1, 0x1, r_std, w_none),
    generator(3, 1, 0x1, r_std, w_none),
    wdth(4, 5, 0x7, r_std, w_none),
    syn_logged(9, 1, 0x0, r_std, w_none),
    version(30, 2, 0x2, r_std, w_none) {
}

int  ordt_rg_stats_features::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_stats_features at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_stats_features\n";
  #endif
     return 8;
}

void  ordt_rg_stats_features::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  adr_logged.write(wdata);
  correctable.write(wdata);
  checker.write(wdata);
  generator.write(wdata);
  wdth.write(wdata);
  syn_logged.write(wdata);
  version.write(wdata);
}

int  ordt_rg_stats_features::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_stats_features at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_stats_features\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_stats_features::read(ordt_data &rdata) {
  rdata.clear();
  for (int widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  adr_logged.read(rdata);
  correctable.read(rdata);
  checker.read(rdata);
  generator.read(rdata);
  wdth.read(rdata);
  syn_logged.read(rdata);
  version.read(rdata);
}

// ------------------ ordt_rg_stats_log_address1 methods ------------------

ordt_rg_stats_log_address1::ordt_rg_stats_log_address1(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    value(0, 10, 0x0, r_std, w_std) {
}

int  ordt_rg_stats_log_address1::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_stats_log_address1 at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_stats_log_address1\n";
  #endif
     return 8;
}

void  ordt_rg_stats_log_address1::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  value.write(wdata);
}

int  ordt_rg_stats_log_address1::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_stats_log_address1 at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_stats_log_address1\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_stats_log_address1::read(ordt_data &rdata) {
  rdata.clear();
  for (int widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  value.read(rdata);
}

// ------------------ ordt_rg_stats_log_address2 methods ------------------

ordt_rg_stats_log_address2::ordt_rg_stats_log_address2(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    value(0, 10, 0x0, r_std, w_std) {
}

int  ordt_rg_stats_log_address2::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_stats_log_address2 at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_stats_log_address2\n";
  #endif
     return 8;
}

void  ordt_rg_stats_log_address2::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  value.write(wdata);
}

int  ordt_rg_stats_log_address2::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_stats_log_address2 at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_stats_log_address2\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_stats_log_address2::read(ordt_data &rdata) {
  rdata.clear();
  for (int widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  value.read(rdata);
}

// ------------------ ordt_rg_stats_wide_reg methods ------------------

ordt_rg_stats_wide_reg::ordt_rg_stats_wide_reg(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    value(0, 96,3, 0, r_std, w_std) {
}

int  ordt_rg_stats_wide_reg::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_stats_wide_reg at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_stats_wide_reg\n";
  #endif
     return 8;
}

void  ordt_rg_stats_wide_reg::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  value.write(wdata);
}

int  ordt_rg_stats_wide_reg::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_stats_wide_reg at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_stats_wide_reg\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_stats_wide_reg::read(ordt_data &rdata) {
  rdata.clear();
  for (int widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  value.read(rdata);
}

// ------------------ ordt_rset_stats methods ------------------

ordt_rset_stats::ordt_rset_stats(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_regset(_m_startaddress, _m_endaddress),
    disable_check(_m_startaddress + 0x0, _m_startaddress + 0x3, 2, 0x80),
    features(_m_startaddress + 0x100, _m_startaddress + 0x103),
    log_address1(_m_startaddress + 0x104, _m_startaddress + 0x107),
    log_address2(_m_startaddress + 0x110, _m_startaddress + 0x113),
    wide_reg(_m_startaddress + 0x120, _m_startaddress + 0x12f) {
  m_children.push_back(&disable_check);
  m_children.push_back(&features);
  m_children.push_back(&log_address1);
  m_children.push_back(&log_address2);
  m_children.push_back(&wide_reg);
}

void  ordt_rset_stats::update_child_ptrs() {
  m_children.clear();
  m_children.push_back(&disable_check);
  m_children.push_back(&features);
  m_children.push_back(&log_address1);
  m_children.push_back(&log_address2);
  m_children.push_back(&wide_reg);
}

// ------------------ ordt_rg_rdr_reorder_window methods ------------------

ordt_rg_rdr_reorder_window::ordt_rg_rdr_reorder_window(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    size(0, 11, 0x80, r_std, w_std),
    set_back(16, 11, 0x10, r_std, w_std),
    ws_enable(31, 1, 0x1, r_std, w_std) {
}

int  ordt_rg_rdr_reorder_window::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_rdr_reorder_window at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_rdr_reorder_window\n";
  #endif
     return 8;
}

void  ordt_rg_rdr_reorder_window::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  size.write(wdata);
  set_back.write(wdata);
  ws_enable.write(wdata);
}

int  ordt_rg_rdr_reorder_window::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_rdr_reorder_window at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_rdr_reorder_window\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_rdr_reorder_window::read(ordt_data &rdata) {
  rdata.clear();
  for (int widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  size.read(rdata);
  set_back.read(rdata);
  ws_enable.read(rdata);
}

// ------------------ ordt_rg_rdr_stream_reconf methods ------------------

ordt_rg_rdr_stream_reconf::ordt_rg_rdr_stream_reconf(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    stream(0, 10, 0x0, r_std, w_std),
    busy(16, 1, 0x0, r_std, w_none) {
}

int  ordt_rg_rdr_stream_reconf::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_rdr_stream_reconf at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_rdr_stream_reconf\n";
  #endif
     return 8;
}

void  ordt_rg_rdr_stream_reconf::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  stream.write(wdata);
  busy.write(wdata);
}

int  ordt_rg_rdr_stream_reconf::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_rdr_stream_reconf at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_rdr_stream_reconf\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_rdr_stream_reconf::read(ordt_data &rdata) {
  rdata.clear();
  for (int widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  stream.read(rdata);
  busy.read(rdata);
}

// ------------------ ordt_rg_rdr_cp_fp_wr_buffer methods ------------------

ordt_rg_rdr_cp_fp_wr_buffer::ordt_rg_rdr_cp_fp_wr_buffer(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    addr1(0, 11, 0, r_std, w_none),
    addr0(16, 11, 0, r_std, w_none) {
}

int  ordt_rg_rdr_cp_fp_wr_buffer::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_rdr_cp_fp_wr_buffer at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_rdr_cp_fp_wr_buffer\n";
  #endif
     return 8;
}

void  ordt_rg_rdr_cp_fp_wr_buffer::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  addr1.write(wdata);
  addr0.write(wdata);
}

int  ordt_rg_rdr_cp_fp_wr_buffer::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_rdr_cp_fp_wr_buffer at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_rdr_cp_fp_wr_buffer\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_rdr_cp_fp_wr_buffer::read(ordt_data &rdata) {
  rdata.clear();
  for (int widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  addr1.read(rdata);
  addr0.read(rdata);
}

// ------------------ ordt_rset_rdr_cp_fp_wr methods ------------------

ordt_rset_rdr_cp_fp_wr::ordt_rset_rdr_cp_fp_wr(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_regset(_m_startaddress, _m_endaddress),
    buffer(_m_startaddress + 0x0, _m_startaddress + 0x3, 4, 0x4) {
  m_children.push_back(&buffer);
}

void  ordt_rset_rdr_cp_fp_wr::update_child_ptrs() {
  m_children.clear();
  m_children.push_back(&buffer);
}

// ------------------ ordt_rg_rdr_roll32_counter_reg methods ------------------

ordt_rg_rdr_roll32_counter_reg::ordt_rg_rdr_roll32_counter_reg(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    count(0, 4, 0x0, r_std, w_std) {
}

int  ordt_rg_rdr_roll32_counter_reg::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_rdr_roll32_counter_reg at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_rdr_roll32_counter_reg\n";
  #endif
     return 8;
}

void  ordt_rg_rdr_roll32_counter_reg::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  count.write(wdata);
}

int  ordt_rg_rdr_roll32_counter_reg::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_rdr_roll32_counter_reg at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_rdr_roll32_counter_reg\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_rdr_roll32_counter_reg::read(ordt_data &rdata) {
  rdata.clear();
  for (int widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  count.read(rdata);
}

// ------------------ ordt_rg_rdr_sat32_counter_reg methods ------------------

ordt_rg_rdr_sat32_counter_reg::ordt_rg_rdr_sat32_counter_reg(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    count(0, 4, 0x0, r_clr, w_std) {
}

int  ordt_rg_rdr_sat32_counter_reg::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_rdr_sat32_counter_reg at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_rdr_sat32_counter_reg\n";
  #endif
     return 8;
}

void  ordt_rg_rdr_sat32_counter_reg::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  count.write(wdata);
}

int  ordt_rg_rdr_sat32_counter_reg::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_rdr_sat32_counter_reg at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_rdr_sat32_counter_reg\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_rdr_sat32_counter_reg::read(ordt_data &rdata) {
  rdata.clear();
  for (int widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  count.read(rdata);
}

// ------------------ ordt_rg_rdr_rcnt_sat_log methods ------------------

ordt_rg_rdr_rcnt_sat_log::ordt_rg_rdr_rcnt_sat_log(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    count(0, 16, 0x0, r_clr, w_std),
    str(16, 10, 0x0, r_clr, w_std),
    subch(26, 5, 0x0, r_clr, w_std),
    en(31, 1, 0x1, r_std, w_std) {
}

int  ordt_rg_rdr_rcnt_sat_log::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_rdr_rcnt_sat_log at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_rdr_rcnt_sat_log\n";
  #endif
     return 8;
}

void  ordt_rg_rdr_rcnt_sat_log::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  count.write(wdata);
  str.write(wdata);
  subch.write(wdata);
  en.write(wdata);
}

int  ordt_rg_rdr_rcnt_sat_log::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_rdr_rcnt_sat_log at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_rdr_rcnt_sat_log\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_rdr_rcnt_sat_log::read(ordt_data &rdata) {
  rdata.clear();
  for (int widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  count.read(rdata);
  str.read(rdata);
  subch.read(rdata);
  en.read(rdata);
}

// ------------------ ordt_rset_rdr methods ------------------

ordt_rset_rdr::ordt_rset_rdr(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_regset(_m_startaddress, _m_endaddress),
    reorder_window(_m_startaddress + 0x0, _m_startaddress + 0x3),
    stream_reconf(_m_startaddress + 0x4, _m_startaddress + 0x7),
    cp_fp_wr(_m_startaddress + 0x21c0, _m_startaddress + 0x21cf),
    roll32_counter_reg(_m_startaddress + 0x21d0, _m_startaddress + 0x21d3),
    sat32_counter_reg(_m_startaddress + 0x21d4, _m_startaddress + 0x21d7),
    rcnt_sat_log(_m_startaddress + 0x21d8, _m_startaddress + 0x21db) {
  m_children.push_back(&reorder_window);
  m_children.push_back(&stream_reconf);
  m_children.push_back(&cp_fp_wr);
  m_children.push_back(&roll32_counter_reg);
  m_children.push_back(&sat32_counter_reg);
  m_children.push_back(&rcnt_sat_log);
}

void  ordt_rset_rdr::update_child_ptrs() {
  m_children.clear();
  m_children.push_back(&reorder_window);
  m_children.push_back(&stream_reconf);
  m_children.push_back(&cp_fp_wr);
  m_children.push_back(&roll32_counter_reg);
  m_children.push_back(&sat32_counter_reg);
  m_children.push_back(&rcnt_sat_log);
}

// ------------------ ordt_rg_extra_reg methods ------------------

ordt_rg_extra_reg::ordt_rg_extra_reg(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_reg(_m_startaddress, _m_endaddress),
    value(0, 32, 0, r_std, w_std) {
}

int  ordt_rg_extra_reg::write(const uint64_t &addr, const ordt_data &wdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write of reg ordt_rg_extra_reg at addr="<< addr << ", data=" << wdata.to_string() << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->write(wdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> write to invalid address " << addr << " in reg ordt_rg_extra_reg\n";
  #endif
     return 8;
}

void  ordt_rg_extra_reg::write(const ordt_data &wdata) {
  std::lock_guard<std::mutex> m_guard(m_mutex);
  value.write(wdata);
}

int  ordt_rg_extra_reg::read(const uint64_t &addr, ordt_data &rdata) {
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read of reg ordt_rg_extra_reg at addr="<< addr << "\n";
  #endif
     if (this->hasStartAddress(addr)) {
        this->read(rdata);
        return 0;
     }
  #ifdef ORDT_PIO_VERBOSE
     std::cout << "--> read to invalid address " << addr << " in reg ordt_rg_extra_reg\n";
  #endif
     rdata.clear();
     return 8;
}

void  ordt_rg_extra_reg::read(ordt_data &rdata) {
  rdata.clear();
  for (int widx=0; widx<((m_endaddress - m_startaddress + 1)/4); widx++) rdata.push_back(0);
  value.read(rdata);
}

// ------------------ ordt_root methods ------------------

ordt_root::ordt_root()
  : ordt_root(0x0, 0x61df) {
}

ordt_root::ordt_root(uint64_t _m_startaddress, uint64_t _m_endaddress)
  : ordt_regset(_m_startaddress, _m_endaddress),
    stats(_m_startaddress + 0x1000, _m_startaddress + 0x11ff),
    rdr(_m_startaddress + 0x4000, _m_startaddress + 0x7fff),
    extra_reg(_m_startaddress + 0x61dc, _m_startaddress + 0x61df) {
  m_children.push_back(&stats);
  m_children.push_back(&rdr);
  m_children.push_back(&extra_reg);
}

void  ordt_root::update_child_ptrs() {
  m_children.clear();
  m_children.push_back(&stats);
  m_children.push_back(&rdr);
  m_children.push_back(&extra_reg);
}


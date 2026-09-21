#include <stdint.h>
#include <stdbool.h>

#include <psci_trampoline.h>

static
int
emit_load_imm64 (
  uint32_t *out,
  int       rd,
  uint64_t  imm)
{
  bool used_movz = 0;
  int  n         = 0;

  // Go thru each Byte
  for (int hw = 0; hw < 4; hw++) {
    // Extract Half
    uint16_t half = (uint16_t)(imm >> (hw * 16));

    // Skip Empty Data
    if (half == 0 && used_movz) {
	    continue;
	  }

    // Pass MOV Instruction
    if (!used_movz) {
      out[n++] = MOVZ (rd, half, hw);
      used_movz = true;
    } else {
      out[n++] = MOVK (rd, half, hw);
    }
  }

  return n;
}

void
generate_trampoline (
  uint64_t *location,
  uint64_t  entry_point,
  uint64_t  context_id)
{
  int n = 0;

  // Set Code Location
  uint32_t *code = (uint32_t *)location;

  // Create Dynamic Trampoline
  n += emit_load_imm64 (code + n, 0,  context_id);
  n += emit_load_imm64 (code + n, 16, entry_point);
  code[n++] = BR (16);
}

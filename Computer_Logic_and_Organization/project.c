// CDA 3103C Project
// By: Josef Ortiz-Feder
#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
  // Go through every possible ALUControl and perform the designated operation
  if((int)ALUControl == 0)
  {
    *ALUresult = A + B;
  }
  else if ((int)ALUControl == 1)
  {
    *ALUresult = A - B;
  }
  else if((int)ALUControl == 2)
  {
    if((signed)A < (signed)B)
    {
      *ALUresult = 1;
    }
    else
    {
      *ALUresult = 0;
    }
  }
  else if((int)ALUControl == 3)
  {
    if(A < B)
    {
      *ALUresult = 1;
    }
    else
    {
      *ALUresult = 0;
    }
  }
  else if((int)ALUControl == 4)
  {
    *ALUresult = A & B;
  }
  else if((int)ALUControl == 5)
  {
    *ALUresult = A | B;
  }
  else if((int)ALUControl == 6)
  {
    *ALUresult = B << 16;
  }
  else if((int)ALUControl == 7)
  {
    *ALUresult = !A;
  }
  // Check for zero
  if(*ALUresult == 0)
  {
    *Zero = 1;
  }
  else
  {
    *Zero = 0;
  }

}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
  // Check for word alignment and then put the designated instruction from memory to intruction
  if(PC % 4 == 0)
  {
    *instruction = Mem[PC >> 2];
    return 0;
  }
  else
  {
    return 1;
  }

}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
  // Partitioning the instruction using masks
  unsigned dataPart = 31;//0x1f;
  unsigned opPart = 63;//0x0000003f;
  unsigned setPart = 65535;//0x0000ffff;
  unsigned jsecPart = 67108863;//0x03ffffff;

  *op = (instruction >> 26) & opPart;
  *r1 = (instruction >> 21) & dataPart;
  *r2 = (instruction >> 16) & dataPart;
  *r3 = (instruction >> 11) & dataPart;
  *funct = instruction & opPart;
  *offset = instruction & setPart;
  *jsec = instruction & jsecPart;
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
  // Assert or deassert each control variable depending on the operation
  if(op == 0)
  {
    controls->RegDst = 1;
    controls->Jump = 0;
    controls->Branch = 0;
    controls->MemRead = 0;
    controls->MemtoReg = 0;
    controls->ALUOp = 7;
    controls->MemWrite = 0;
    controls->ALUSrc = 0;
    controls->RegWrite = 1;
  }
  else if(op == 8)
  {
    controls->RegDst = 0;
    controls->Jump = 0;
    controls->Branch = 0;
    controls->MemRead = 0;
    controls->MemtoReg = 0;
    controls->ALUOp = 0;
    controls->MemWrite = 0;
    controls->ALUSrc = 1;
    controls->RegWrite = 1;
  }
  else if(op == 15)
  {
    controls->RegDst = 0;
    controls->Jump = 0;
    controls->Branch = 0;
    controls->MemRead = 0;
    controls->MemtoReg = 0;
    controls->ALUOp = 6;
    controls->MemWrite = 0;
    controls->ALUSrc = 1;
    controls->RegWrite = 1;
  }
  else if(op == 35)
  {
    controls->RegDst = 0;
    controls->Jump = 0;
    controls->Branch = 0;
    controls->MemRead = 1;
    controls->MemtoReg = 1;
    controls->ALUOp = 0;
    controls->MemWrite = 0;
    controls->ALUSrc = 1;
    controls->RegWrite = 1;
  }
  else if(op == 43)
  {
    controls->RegDst = 2;
    controls->Jump = 0;
    controls->Branch = 0;
    controls->MemRead = 0;
    controls->MemtoReg = 2;
    controls->ALUOp = 0;
    controls->MemWrite = 1;
    controls->ALUSrc = 1;
    controls->RegWrite = 0;
  }
  else if(op == 4)
  {
    controls->RegDst = 2;
    controls->Jump = 0;
    controls->Branch = 1;
    controls->MemRead = 0;
    controls->MemtoReg = 2;
    controls->ALUOp = 1;
    controls->MemWrite = 0;
    controls->ALUSrc = 0;
    controls->RegWrite = 0;
  }
  else if(op == 10)
  {
    controls->RegDst = 1;
    controls->Jump = 0;
    controls->Branch = 0;
    controls->MemRead = 0;
    controls->MemtoReg = 0;
    controls->ALUOp = 2;
    controls->MemWrite = 0;
    controls->ALUSrc = 0;
    controls->RegWrite = 1;
  }
  else if(op == 11)
  {
    controls->RegDst = 1;
    controls->Jump = 0;
    controls->Branch = 0;
    controls->MemRead = 0;
    controls->MemtoReg = 0;
    controls->ALUOp = 3;
    controls->MemWrite = 0;
    controls->ALUSrc = 0;
    controls->RegWrite = 1;
  }
  else if(op == 2)
  {
    controls->RegDst = 2;
    controls->Jump = 1;
    controls->Branch = 0;
    controls->MemRead = 0;
    controls->MemtoReg = 0;
    controls->ALUOp = 0;
    controls->MemWrite = 0;
    controls->ALUSrc = 0;
    controls->RegWrite = 0;
  }
  else
  {
    return 1;
  }
  return 0;
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
  // Put the data from register into data1 and data2 based on r1 and r2
  *data1 = Reg[r1];
  *data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
  // Extend the offset variable by determining if the first bit is a 1 and then filling the rest with either 0's or 1's
  unsigned testBit = offset >> 15;

  if(testBit == 1)
  {
    *extended_value = offset | 0xFFFF0000;
  }
  else
  {
    *extended_value = offset & 0x0000ffff;
  }
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
  // Get the ALUOp based on the funct and then run the ALU function to actually run the operation
  if(ALUSrc == 1)
  {
    data2 = extended_value;
  }

  if(ALUOp == 7)
  {
    if(funct == 32)
    {
      ALUOp = 0;
    }
    else if(funct == 34)
    {
      ALUOp = 1;
    }
    else if(funct == 42)
    {
      ALUOp = 2;
    }
    else if(funct == 43)
    {
      ALUOp = 3;
    }
    else if(funct == 36)
    {
      ALUOp = 4;
    }
    else if(funct == 37)
    {
      ALUOp = 5;
    }
    else if(funct == 4)
    {
      ALUOp = 6;
    }
    else if(funct == 39)
    {
      ALUOp = 7;
    }
    // If funct is invalid, then halt
    else
    {
      return 1;
    }
    ALU(data1, data2, ALUOp, ALUresult, Zero);
  }
  else
  {
    ALU(data1, data2, ALUOp, ALUresult, Zero);
  }
  return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

  if(MemWrite == 1)
  {
    // Check for word alignment
    if(ALUresult % 4 == 0)
    {
      // Because we are writing, we write to the Memory (Mem)
      Mem[ALUresult >> 2] = data2;
    }
    else
    {
      return 1;
    }
  }
  else if(MemRead == 1)
  {
    // Check for word alignment
    if(ALUresult % 4 == 0)
    {
      // Because we are reading, we read from the Memory (Mem)
      *memdata = Mem[ALUresult >> 2];
    }
    else
    {
      return 1;
    }
  }
  return 0;

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
  // Only perform this if we are given permission to write
  if(RegWrite == 1)
  {
    // Only perform this if we are not given permission to MemtoReg
    if(MemtoReg == 0)
    {
      // Depending on RegDst and its value, place ALUresult Reg[r2] or Reg[r3]
      if(RegDst == 0)
      {
        Reg[r2] = ALUresult;
      }
      else
      {
        Reg[r3] = ALUresult;
      }
    }
    // Only perform this if we are given permission to MemtoReg
    else if(MemtoReg == 1)
    {
      // Write to Reg based on the location designated by RegDst
      if(RegDst == 0)
      {
        Reg[r2] = memdata;
      }
      else
      {
        Reg[r3] = memdata;
      }
    }
  }
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
  // Iterate PC (always by 4)
  *PC += 4;

  if(Zero == 1 && Branch == 1)
  {
    *PC += extended_value << 2;
  }

  if(Jump == 1)
  {
    *PC = (jsec << 2) | (*PC & 0xf0000000);
  }
}

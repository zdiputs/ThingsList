/*********************************************************************************
  Auth:火星火箭      (z)diputs 
  http:iamrobot.top https://github.com/zdiputs
  https:stgui.com   https://gitee.com/diputs
********************************************************************************/
#include "main.h"
#include "oled.h"
#include "oledfont.h"
#include "stm32f4xx_hal_flash.h"
const GBX16 Hzk[] = {
  "正", 0x00, 0x02, 0x02, 0xC2, 0x02, 0x02, 0x02, 0xFE,
  0x82, 0x82, 0x82, 0xC2, 0x83, 0x02, 0x00, 0x00,
  0x40, 0x40, 0x40, 0x7F, 0x40, 0x40, 0x40, 0x7F,
  0x40, 0x40, 0x40, 0x40, 0x40, 0x60, 0x40, 0x00,
  
  "常", 0x20, 0x18, 0x08, 0x0A, 0xEC, 0xA8, 0xA8, 0xAF,
  0xA8, 0xA8, 0xEC, 0x0A, 0x08, 0x28, 0x18, 0x00,
  0x00, 0x00, 0x00, 0x3E, 0x02, 0x02, 0x02, 0xFF,
  0x02, 0x22, 0x42, 0x3F, 0x02, 0x00, 0x00, 0x00,
  
  "错", 0x80, 0x40, 0x70, 0xCF, 0x48, 0x48, 0x48, 0x48,
  0x7F, 0x48, 0x48, 0x7F, 0xC8, 0x68, 0x40, 0x00,
  0x00, 0x02, 0x02, 0x7F, 0x22, 0x12, 0x00, 0xFF,
  0x49, 0x49, 0x49, 0x49, 0xFF, 0x01, 0x00, 0x00,
  
  "误", 0x40, 0x42, 0xC4, 0x0C, 0x00, 0x40, 0x5E, 0x52,
  0x52, 0xD2, 0x52, 0x52, 0x5F, 0x42, 0x00, 0x00,
  0x00, 0x00, 0x7F, 0x20, 0x12, 0x82, 0x42, 0x22,
  0x1A, 0x07, 0x1A, 0x22, 0x42, 0xC3, 0x42, 0x00,
  "运", 0x40, 0x42, 0x44, 0xCC, 0x00, 0x20, 0x22, 0x22,
  0xE2, 0x22, 0x22, 0x23, 0x32, 0x20, 0x00, 0x00,
  0x00, 0x40, 0x20, 0x1F, 0x20, 0x48, 0x4C, 0x4B,
  0x48, 0x48, 0x4A, 0x4C, 0x58, 0x60, 0x20, 0x00,
  
  "行", 0x00, 0x10, 0x88, 0xC4, 0x23, 0x40, 0x42, 0x42,
  0x42, 0x42, 0x42, 0xC2, 0x43, 0x62, 0x40, 0x00,
  0x02, 0x01, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x40, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00,
  
  "状", 0x00, 0x08, 0x30, 0x00, 0xFF, 0x20, 0x20, 0x20,
  0x20, 0xFF, 0x20, 0x22, 0x24, 0x30, 0x20, 0x00,
  0x08, 0x0C, 0x02, 0x01, 0xFF, 0x40, 0x20, 0x1C,
  0x03, 0x00, 0x03, 0x0C, 0x30, 0x60, 0x20, 0x00,
  
  "态", 0x04, 0x04, 0x84, 0x84, 0x44, 0x24, 0x54, 0x8F,
  0x14, 0x24, 0x44, 0x44, 0x84, 0x86, 0x84, 0x00,
  0x01, 0x21, 0x1C, 0x00, 0x3C, 0x40, 0x42, 0x4C,
  0x40, 0x40, 0x70, 0x04, 0x08, 0x31, 0x00, 0x00,
  "模", 0x10, 0x10, 0xD0, 0xFF, 0x94, 0x14, 0xE4, 0xBF,
  0xA4, 0xA4, 0xA4, 0xBF, 0xF4, 0x26, 0x04, 0x00,
  0x04, 0x03, 0x00, 0xFF, 0x08, 0x89, 0x8B, 0x4A,
  0x2A, 0x1E, 0x2A, 0x2A, 0x4B, 0xC8, 0x48, 0x00,
  
  "块", 0x20, 0x20, 0x20, 0xFF, 0x20, 0x20, 0x10, 0x10,
  0xFF, 0x10, 0x10, 0x10, 0xF8, 0x10, 0x00, 0x00,
  0x08, 0x18, 0x08, 0x0F, 0x84, 0x46, 0x22, 0x1A,
  0x07, 0x0A, 0x12, 0x22, 0x43, 0xC2, 0x42, 0x00,
  
  "数", 0x10, 0x92, 0x54, 0x30, 0xFF, 0x50, 0x94, 0x32,
  0xD8, 0x17, 0x10, 0x10, 0xF0, 0x18, 0x10, 0x00,
  0x02, 0x82, 0x4E, 0x33, 0x22, 0x52, 0x8E, 0x40,
  0x23, 0x14, 0x08, 0x16, 0x61, 0xC0, 0x40, 0x00,
  "校", 0x10, 0x10, 0xD0, 0xFF, 0x90, 0x10, 0x88, 0x48,
  0xA8, 0x09, 0x0A, 0x08, 0xA8, 0x4C, 0xC8, 0x00,
  0x04, 0x03, 0x00, 0xFF, 0x80, 0x81, 0x40, 0x40,
  0x21, 0x16, 0x08, 0x16, 0x61, 0xC0, 0x40, 0x00,
  
  "准", 0x00, 0x02, 0x04, 0xEC, 0x40, 0x20, 0xF8, 0x4F,
  0x48, 0x49, 0xFE, 0x48, 0x68, 0x4C, 0x08, 0x00,
  0x02, 0x02, 0x7F, 0x00, 0x00, 0x00, 0xFF, 0x22,
  0x22, 0x22, 0x3F, 0x22, 0x23, 0x32, 0x20, 0x00,
  
  "波", 0x20, 0x42, 0x04, 0x0C, 0x80, 0xF8, 0x88, 0x88,
  0x88, 0xFF, 0x88, 0x88, 0xA8, 0x18, 0x00, 0x00,
  0x04, 0x04, 0xFE, 0x41, 0x30, 0x8F, 0x40, 0x22,
  0x14, 0x08, 0x14, 0x22, 0x41, 0xC0, 0x40, 0x00,
  
  "特", 0x20, 0x1C, 0x10, 0xFF, 0x90, 0x50, 0x48, 0x48,
  0x48, 0x7F, 0x48, 0xC8, 0x4C, 0x68, 0x40, 0x00,
  0x02, 0x02, 0x01, 0xFF, 0x00, 0x02, 0x02, 0x06,
  0x1A, 0x42, 0x82, 0x7F, 0x02, 0x03, 0x02, 0x00,
  
  "率", 0x00, 0x14, 0xA4, 0x44, 0x04, 0x24, 0xB5, 0x6E,
  0x24, 0x94, 0x04, 0x44, 0xA6, 0x14, 0x00, 0x00,
  0x08, 0x09, 0x08, 0x08, 0x09, 0x09, 0x09, 0xFF,
  0x09, 0x09, 0x0B, 0x08, 0x08, 0x0D, 0x08, 0x00,
  
  "地", 0x40, 0x40, 0xFE, 0x40, 0x40, 0x80, 0xFC, 0x40,
  0x40, 0xFF, 0x20, 0x20, 0xF0, 0x20, 0x00, 0x00,
  0x20, 0x60, 0x3F, 0x10, 0x10, 0x00, 0x3F, 0x40,
  0x40, 0x5F, 0x44, 0x48, 0x47, 0x40, 0x70, 0x00,
  
  "址", 0x10, 0x10, 0x10, 0xFF, 0x10, 0x18, 0x10, 0xF8,
  0x00, 0x00, 0xFF, 0x20, 0x20, 0x30, 0x20, 0x00,
  0x20, 0x60, 0x20, 0x3F, 0x10, 0x50, 0x48, 0x7F,
  0x40, 0x40, 0x7F, 0x40, 0x40, 0x60, 0x40, 0x00,
  "过", 0x40, 0x42, 0x44, 0xC8, 0x00, 0x08, 0x08, 0x48,
  0x88, 0x08, 0x08, 0xFF, 0x08, 0x08, 0x00, 0x00,
  0x00, 0x40, 0x20, 0x1F, 0x20, 0x40, 0x40, 0x40,
  0x41, 0x48, 0x50, 0x4F, 0x40, 0x60, 0x20, 0x00,
  
  "触", 0x20, 0xF8, 0x27, 0xF4, 0x2C, 0xE4, 0x00, 0xF0,
  0x10, 0x10, 0xFF, 0x10, 0x10, 0xF8, 0x10, 0x00,
  0x80, 0x7F, 0x09, 0x7F, 0x89, 0xFF, 0x00, 0x4F,
  0xC4, 0x44, 0x7F, 0x24, 0x34, 0x27, 0xC0, 0x00,
  
  "发", 0x00, 0x10, 0x18, 0x16, 0x10, 0x90, 0xF0, 0x9F,
  0x90, 0x90, 0x92, 0x94, 0x10, 0x18, 0x10, 0x00,
  0x40, 0x20, 0x90, 0x88, 0x46, 0x41, 0x23, 0x14,
  0x08, 0x14, 0x22, 0x21, 0x40, 0xC0, 0x40, 0x00,
  "欠", 0x80, 0x40, 0x20, 0x18, 0x0F, 0x08, 0x08, 0xE8,
  0x08, 0x08, 0x08, 0x48, 0x28, 0x18, 0x00, 0x00,
  0x80, 0x80, 0x40, 0x20, 0x10, 0x0C, 0x03, 0x00,
  0x03, 0x0C, 0x10, 0x20, 0x40, 0xC0, 0x40, 0x00,
  
  "补", 0x10, 0x10, 0x10, 0x11, 0xD6, 0x30, 0x98, 0x00,
  0x00, 0xFF, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x04, 0x02, 0x01, 0xFF, 0x01, 0x02, 0x00,
  0x00, 0xFF, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00,
  
  "偿", 0x80, 0x40, 0x20, 0xF8, 0x47, 0x30, 0x92, 0x94,
  0x90, 0x9F, 0x90, 0xD4, 0x92, 0x50, 0x30, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0x04, 0x04, 0x44, 0x64,
  0x54, 0x4C, 0x44, 0x54, 0x64, 0xC6, 0x04, 0x00,
  "直", 0x00, 0x04, 0x04, 0xE4, 0xA4, 0xA4, 0xA4, 0xBF,
  0xA4, 0xA4, 0xA4, 0xF4, 0x26, 0x04, 0x00, 0x00,
  0x40, 0x40, 0x40, 0x7F, 0x4A, 0x4A, 0x4A, 0x4A,
  0x4A, 0x4A, 0x4A, 0x7F, 0x40, 0x60, 0x40, 0x00,
  "市", 0x08, 0x08, 0xC8, 0x48, 0x48, 0x48, 0x49, 0xFA,
  0x48, 0x48, 0x48, 0x48, 0xE8, 0x4C, 0x08, 0x00,
  0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0x00, 0x00, 0x10, 0x20, 0x1F, 0x00, 0x00, 0x00,
  
  "报", 0x10, 0x10, 0x10, 0xFF, 0x90, 0x50, 0x00, 0xFE,
  0x82, 0x82, 0x92, 0xA2, 0x9F, 0x02, 0x00, 0x00,
  0x02, 0x42, 0x81, 0x7F, 0x00, 0x00, 0x00, 0xFF,
  0x22, 0x14, 0x08, 0x16, 0x21, 0x60, 0x20, 0x00,
  
  "警", 0x80, 0x92, 0x8A, 0xBF, 0xAA, 0xBB, 0xCA, 0xFA,
  0x84, 0xA7, 0xAA, 0x92, 0xAE, 0xE2, 0xA0, 0x00,
  0x00, 0x00, 0x00, 0xEA, 0xAA, 0xAA, 0xAA, 0xAA,
  0xAA, 0xAA, 0xAA, 0xEA, 0x00, 0x00, 0x00, 0x00,
  "离", 0x04, 0x04, 0x04, 0xF4, 0x04, 0x8C, 0x55, 0x26,
  0x54, 0x8C, 0x04, 0xF4, 0x04, 0x06, 0x04, 0x00,
  0x00, 0xFC, 0x04, 0x05, 0x25, 0x35, 0x2D, 0x27,
  0x25, 0x35, 0x25, 0x45, 0x84, 0x7E, 0x04, 0x00,
  "在", 0x08, 0x08, 0x08, 0x08, 0xC8, 0x38, 0x0F, 0x08,
  0x08, 0xE8, 0x08, 0x88, 0x08, 0x0C, 0x08, 0x00,
  0x08, 0x04, 0x02, 0xFF, 0x00, 0x40, 0x41, 0x41,
  0x41, 0x7F, 0x41, 0x41, 0x41, 0x60, 0x40, 0x00,
  "线", 0x00, 0x20, 0x30, 0xAC, 0x63, 0x20, 0x30, 0x20,
  0x20, 0xFF, 0x90, 0x92, 0x94, 0xD0, 0x80, 0x00,
  0x20, 0x62, 0x23, 0x12, 0x12, 0x12, 0x41, 0x41,
  0x21, 0x17, 0x18, 0x24, 0x42, 0x80, 0xE0, 0x00,
  "模", 0x10, 0x10, 0xD0, 0xFF, 0x94, 0x14, 0xE4, 0xBF,
  0xA4, 0xA4, 0xA4, 0xBF, 0xF4, 0x26, 0x04, 0x00,
  0x04, 0x03, 0x00, 0xFF, 0x08, 0x89, 0x8B, 0x4A,
  0x2A, 0x1E, 0x2A, 0x2A, 0x4B, 0xC8, 0x48, 0x00,
  "块", 0x20, 0x20, 0x20, 0xFF, 0x20, 0x20, 0x10, 0x10,
  0xFF, 0x10, 0x10, 0x10, 0xF8, 0x10, 0x00, 0x00,
  0x08, 0x18, 0x08, 0x0F, 0x84, 0x46, 0x22, 0x1A,
  0x07, 0x0A, 0x12, 0x22, 0x43, 0xC2, 0x42, 0x00,
  "启", 0x00, 0x00, 0x00, 0xFC, 0x44, 0x44, 0x44, 0x45,
  0x46, 0x44, 0x44, 0x44, 0x44, 0x7E, 0x04, 0x00,
  0x40, 0x20, 0x18, 0x07, 0xFE, 0x42, 0x42, 0x42,
  0x42, 0x42, 0x42, 0x42, 0x42, 0xFF, 0x02, 0x00,
  "用", 0x00, 0x00, 0xFE, 0x22, 0x22, 0x22, 0x22, 0xFE,
  0x22, 0x22, 0x22, 0x22, 0xFF, 0x02, 0x00, 0x00,
  0x80, 0x60, 0x1F, 0x02, 0x02, 0x02, 0x02, 0x7F,
  0x02, 0x02, 0x42, 0x82, 0x7F, 0x00, 0x00, 0x00,
  "屏", 0x00, 0x00, 0xFE, 0x12, 0x92, 0x92, 0xB2, 0xD2,
  0x92, 0xD2, 0xB2, 0x92, 0xDF, 0x82, 0x00, 0x00,
  0x40, 0x20, 0x1F, 0x04, 0x84, 0x44, 0x3F, 0x04,
  0x04, 0x04, 0xFF, 0x04, 0x04, 0x06, 0x04, 0x00,
  "蔽", 0x04, 0x94, 0xA4, 0x84, 0xF4, 0xCF, 0xA4, 0x94,
  0x04, 0x8F, 0x74, 0x44, 0x44, 0xE6, 0x44, 0x00,
  0x00, 0xFF, 0x08, 0x04, 0x3F, 0x04, 0x88, 0xFF,
  0x81, 0x40, 0x2F, 0x10, 0x28, 0xC7, 0x40, 0x00,
  
  "设", 0x40, 0x40, 0x42, 0xCC, 0x00, 0x40, 0xA0, 0x9F,
  0x81, 0x81, 0x81, 0x9F, 0xA0, 0x20, 0x20, 0x00,
  0x00, 0x00, 0x00, 0x7F, 0xA0, 0x90, 0x40, 0x43,
  0x2C, 0x10, 0x28, 0x26, 0x41, 0xC0, 0x40, 0x00,
  "置", 0x00, 0x10, 0x17, 0xD5, 0x55, 0x57, 0x55, 0x7D,
  0x55, 0x57, 0x55, 0xD5, 0x17, 0x10, 0x00, 0x00,
  0x40, 0x40, 0x40, 0x7F, 0x55, 0x55, 0x55, 0x55,
  0x55, 0x55, 0x55, 0x7F, 0x40, 0x60, 0x40, 0x00,
  "出", 0x00, 0x00, 0xFC, 0x40, 0x40, 0x40, 0x40, 0xFF,
  0x40, 0x40, 0x40, 0x40, 0xFC, 0x00, 0x00, 0x00,
  0x00, 0xFE, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7F,
  0x40, 0x40, 0x40, 0x40, 0x40, 0xFE, 0x00, 0x00,
  "开", 0x80, 0x82, 0x82, 0x82, 0xFE, 0x82, 0x82, 0x82,
  0x82, 0x82, 0xFE, 0x82, 0x83, 0xC2, 0x80, 0x00,
  0x00, 0x80, 0x40, 0x30, 0x0F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
  "关", 0x00, 0x10, 0x10, 0x11, 0x12, 0x1C, 0x10, 0xF0,
  0x10, 0x18, 0x14, 0x13, 0x1A, 0x90, 0x00, 0x00,
  0x81, 0x81, 0x41, 0x41, 0x21, 0x11, 0x0D, 0x03,
  0x0D, 0x11, 0x21, 0x21, 0x41, 0xC1, 0x41, 0x00,
  "温", 0x10, 0x22, 0x64, 0x0C, 0x80, 0x00, 0xFE, 0x92,
  0x92, 0x92, 0x92, 0x92, 0xFF, 0x02, 0x00, 0x00,
  0x04, 0x04, 0xFE, 0x01, 0x40, 0x7E, 0x42, 0x42,
  0x7E, 0x42, 0x7E, 0x42, 0x42, 0x7E, 0x40, 0x00,
  "度", 0x00, 0x00, 0xFC, 0x24, 0x24, 0x24, 0xFC, 0xA5,
  0xA6, 0xA4, 0xFC, 0x24, 0x34, 0x26, 0x04, 0x00,
  0x40, 0x20, 0x9F, 0x80, 0x42, 0x42, 0x26, 0x2A,
  0x12, 0x2A, 0x26, 0x42, 0x40, 0xC0, 0x40, 0x00,
  "℃", 0x00, 0x06, 0x09, 0x09, 0xE6, 0xF0, 0x18, 0x08,
  0x08, 0x08, 0x18, 0x30, 0x78, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x18, 0x30,
  0x20, 0x20, 0x20, 0x10, 0x08, 0x00, 0x00, 0x00,
  "退", 0x40, 0x42, 0x44, 0xCC, 0x00, 0x00, 0xFF, 0x49,
  0x49, 0x49, 0x49, 0x49, 0xFF, 0x40, 0x00, 0x00,
  0x00, 0x40, 0x20, 0x1F, 0x20, 0x40, 0x9F, 0x88,
  0x85, 0x81, 0x82, 0x85, 0x88, 0xD8, 0x40, 0x00,
  "电", 0x00, 0xF8, 0x48, 0x48, 0x48, 0x48, 0xFF, 0x48,
  0x48, 0x48, 0x48, 0xFC, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x07, 0x02, 0x02, 0x02, 0x02, 0x3F, 0x42,
  0x42, 0x42, 0x42, 0x47, 0x40, 0x70, 0x00, 0x00,
  "压", 0x00, 0x00, 0xFE, 0x02, 0x82, 0x82, 0x82, 0x82,
  0xFE, 0x82, 0x82, 0x82, 0xC3, 0x82, 0x00, 0x00,
  0x40, 0x30, 0x0F, 0x40, 0x40, 0x40, 0x40, 0x40,
  0x7F, 0x40, 0x42, 0x44, 0x4C, 0x60, 0x40, 0x00,
  "流", 0x10, 0x22, 0x64, 0x0C, 0x80, 0x44, 0x44, 0x64,
  0x55, 0x4E, 0x44, 0x54, 0x66, 0xC4, 0x00, 0x00,
  0x04, 0x04, 0xFE, 0x01, 0x00, 0x80, 0x40, 0x3F,
  0x00, 0xFF, 0x00, 0x3F, 0x40, 0x40, 0x70, 0x00,
  
  "查", 0x84, 0x84, 0x44, 0xE4, 0x54, 0x4C, 0x44, 0x7F,
  0x44, 0x4C, 0x54, 0xE4, 0x44, 0xC6, 0x44, 0x00,
  0x40, 0x40, 0x40, 0x5F, 0x52, 0x52, 0x52, 0x52,
  0x52, 0x52, 0x52, 0x5F, 0x40, 0x60, 0x40, 0x00,
  
  "看", 0x20, 0x2A, 0x2A, 0xAA, 0xEA, 0xBA, 0xAE, 0xAA,
  0xAA, 0xA9, 0xA9, 0xED, 0xA8, 0x20, 0x20, 0x00,
  0x04, 0x02, 0x01, 0xFF, 0x4A, 0x4A, 0x4A, 0x4A,
  0x4A, 0x4A, 0x4A, 0xFF, 0x00, 0x00, 0x00, 0x00,
  
  "交", 0x08, 0x08, 0x88, 0x48, 0xB8, 0x08, 0x09, 0x0E,
  0x08, 0x08, 0x98, 0x28, 0x48, 0xCC, 0x08, 0x00,
  0x80, 0x81, 0x40, 0x40, 0x20, 0x11, 0x0A, 0x04,
  0x0A, 0x11, 0x20, 0x20, 0x40, 0xC0, 0x40, 0x00};

void delay_ns(unsigned int ndelay)
{
  unsigned int i = 0;
  for (i = 0; i < 1; i++)
  {
    ;
  }
}

void delay_us(unsigned int ndelay)
{
  
  for (; ndelay > 0; ndelay--)
  {
    delay_ns(1000);
  }
}

void delay_ms(unsigned int ndelay)
{
  
  for (; ndelay > 0; ndelay--)
  {
    delay_us(1000);
  }
}
void SDA_Out(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; //输出
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
//设置数据线为输入
void SDA_In(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; //输入
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

//--------------------------------------------------------
//启动总线
//--------------------------------------------------------

void IIC_Start()
{
  SDA_Out();
  SDA_H;
  SCL_H;
  delay_us(2);
  SDA_L;
  delay_us(2);
  SCL_L;
  delay_us(2);
}
//--------------------------------------------------------
//释放总线
//--------------------------------------------------------

void IIC_Stop()
{
  IIC_Start();
  SCL_H;
  SDA_L;
  delay_us(2);
  SDA_H;
  delay_us(2);
}
//------------------------------------------------------
//读应答
//------------------------------------------------------

unsigned char Read_Ask(void)
{
  unsigned char ReAsk;
  SDA_In();
  SCL_H;
  delay_us(2);
  ReAsk = (unsigned char)SDA_READ;
  SCL_L;
  delay_us(2);
  return ReAsk;
}
//-----------------------------------------------------
//写入一个字节
//-----------------------------------------------------
void Write_OneByte(unsigned char Dat)
{
  unsigned char i;
  SDA_Out();
  for (i = 0; i < 8; i++)
  {
    if (Dat & 0x80)
    {
      SDA_H;
    }
    else
    {
      SDA_L;
    }
    Dat <<= 1;
    SCL_H;
    delay_us(2);
    SCL_L;
    delay_us(2);
  }
  Read_Ask();
}

//------------------------------------------------------
//写命令
//------------------------------------------------------
void WriteCmd(unsigned char IIC_Cmd)
{
  IIC_Start();
  Write_OneByte(0x78);
  Write_OneByte(0x00);
  Write_OneByte(IIC_Cmd);
  IIC_Stop();
}
//------------------------------------------------------
//写数据
//------------------------------------------------------
void WriteDat(unsigned char IIC_Dat)
{
  IIC_Start();
  Write_OneByte(0x78);
  Write_OneByte(0x40);
  Write_OneByte(IIC_Dat);
  IIC_Stop();
}
//-----------------------------------------------------
// OLED初始化
//-----------------------------------------------------
void OLED_Init(void)
{
  SDA_Out();
  
  delay_ms(800);
  WriteCmd(0xae);
  WriteCmd(0x00);
  WriteCmd(0x10);
  WriteCmd(0x40);
  WriteCmd(0x81);
  WriteCmd(0xcf);
  WriteCmd(0xa1);
  WriteCmd(0xc8);
  WriteCmd(0xa6);
  WriteCmd(0xa8);
  WriteCmd(0x3f);
  WriteCmd(0xd3);
  WriteCmd(0x00);
  WriteCmd(0xd5);
  WriteCmd(0x80);
  WriteCmd(0xd9);
  WriteCmd(0xf1);
  WriteCmd(0xda);
  WriteCmd(0x12);
  WriteCmd(0xdb);
  WriteCmd(0x40);
  WriteCmd(0x20);
  WriteCmd(0x02);
  WriteCmd(0x8d);
  WriteCmd(0x14);
  WriteCmd(0xa4);
  WriteCmd(0xa6);
  WriteCmd(0xaf);
}

//-----------------------------------------------------------------------
// OLED全屏填充
//----------------------------------------------------------------------
void OLED_Fill(unsigned char fill_Data)
{
  unsigned char m, n;
  for (m = 0; m < 8; m++)
  {
    WriteCmd(0xb0 + m);
    WriteCmd(0x00);
    WriteCmd(0x10);
    for (n = 0; n < 128; n++)
    {
      WriteDat(fill_Data);
    }
  }
}
//--------------------------------------------------------------
void OLED_CLS(void)
{
  OLED_Fill(0x00);
}
//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          :
// Parameters     : none
// Description    : 将OLED从休眠中唤醒
//--------------------------------------------------------------

void OLED_ON(void)
{
  WriteCmd(0x8d);
  WriteCmd(0x10);
  WriteCmd(0xae);
}

//-------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          :
// Parameters     : none
// Description    : 让OLED休眠
//------------------------------------------------------------
void OLED_OFF(void)
{
  WriteCmd(0x8d);
  WriteCmd(0x10);
  WriteCmd(0xae);
}

//----------------------------------------------------------------------
//设置坐标
//----------------------------------------------------------------------
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
  WriteCmd(0xb0 + y);
  WriteCmd(((x & 0xf0) >> 4) | 0x10);
  WriteCmd((x & 0x0f));
}

//显示汉字
//取模方式 纵向8点上高位置
// OLED_ShowCHinese (i*8+8*ucX,ucY,(unsigned char *)&Hzk[0].Msk[0],revyn);
void OLED_ShowCHinese(unsigned char x, unsigned char y, unsigned char *chn, unsigned char revshow)
{
  unsigned char t, adder = 0;
  if (revshow == 0)
  {
    OLED_Set_Pos(x, y);
    for (t = 0; t < 16; t++)
    {
      WriteDat(*chn++);
      adder += 1;
    }
    OLED_Set_Pos(x, y + 1);
    for (t = 0; t < 16; t++)
    {
      WriteDat(*chn++);
      adder += 1;
    }
  }
  else
  {
    OLED_Set_Pos(x, y);
    for (t = 0; t < 16; t++)
    {
      WriteDat(~(*chn++));
      adder += 1;
    }
    OLED_Set_Pos(x, y + 1);
    for (t = 0; t < 16; t++)
    {
      WriteDat(~(*chn++));
      adder += 1;
    }
  }
}

//-----------------------------------------------------------------------------

static unsigned char str[16] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
static char mycabs(char val)
{
  return (val > 0 ? val : (val * -1));
}

void Char2Str(signed char Data, unsigned char Len, unsigned char DecLen,  char *pStr)
{
  unsigned char i;
  unsigned char minus;
  unsigned char uData;
  
  // validity check
  *pStr = '\0';
  if (Len <= DecLen)
    return;
  //	if(DecLen == 0 && Len <= 1) return;
  if (DecLen && Len < (DecLen + 2))
    return;
  
  uData = mycabs(Data);
  if (Data < 0)
    minus = '-';
  else
    minus = ' ';
  
  pStr += Len;
  *pStr-- = '\0';
  i = 0;
  // decimal portion
  while (i < DecLen)
  {
    *pStr-- = uData % 10 + '0';
    uData /= 10;
    i++;
  }
  
  // decimal point
  if (DecLen)
  {
    *pStr-- = '.';
    i++;
  }
  // integer before point.
  *pStr-- = uData % 10 + '0';
  uData /= 10;
  i++;
  // rest integer
  while (i < Len - 1 && uData)
  {
    *pStr-- = uData % 10 + '0';
    uData /= 10;
    i++;
  }
  // sign
  *pStr-- = minus;
  i++;
  // rest blank
  while (i < Len)
  {
    *pStr-- = ' ';
    i++;
  }
}

void uChar2Hex(unsigned char uData, unsigned char Len, unsigned char DecLen, unsigned char *pStr)
{
  unsigned char i;
  
  // validity check
  *pStr = '\0';
  if (Len <= DecLen)
    return;
  //	if(DecLen == 0 && Len <= 1) return;
  if (DecLen && Len < (DecLen + 2))
    return;
  
  pStr += Len; // move to head postion
  *pStr-- = '\0';
  i = 0;
  // decimal portion
  while (i < DecLen)
  {
    *pStr-- = uData % 10 + '0';
    uData /= 10;
    i++;
  }
  
  // decimal point
  if (DecLen)
  {
    *pStr-- = '.';
    i++;
  }
  // integer before point.
  *pStr-- = str[uData % 16];
  uData /= 16;
  i++;
  // rest integer
  while (i < Len && uData)
  {
    *pStr-- = str[uData % 16];
    uData /= 16;
    i++;
  }
  // rest blank
  while (i < Len)
  {
    *pStr-- = '0';
    i++;
  }
}

void uChar2Str(unsigned char uData, unsigned char Len, unsigned char DecLen,  char *pStr)
{
  unsigned char i;
  
  // validity check
  *pStr = '\0';
  if (Len <= DecLen)
    return;
  //	if(DecLen == 0 && Len <= 1) return;
  if (DecLen && Len < (DecLen + 2))
    return;
  
  pStr += Len;
  *pStr-- = '\0';
  i = 0;
  // decimal portion
  while (i < DecLen)
  {
    *pStr-- = uData % 10 + '0';
    uData /= 10;
    i++;
  }
  
  // decimal point
  if (DecLen)
  {
    *pStr-- = '.';
    i++;
  }
  // integer before point.
  *pStr-- = uData % 10 + '0';
  uData /= 10;
  i++;
  // rest integer
  while (i < Len && uData)
  {
    *pStr-- = uData % 10 + '0';
    uData /= 10;
    i++;
  }
  // rest blank
  while (i < Len)
  {
    *pStr-- = ' ';
    i++;
  }
}

// Len: total length of the string. include decimal portion, decimal point, integer portion and sign.
// DecLen exclude decimal point.
void Int2Str(signed short Data, unsigned char Len, unsigned char DecLen,  char *pStr)
{
  unsigned char i;
  unsigned char minus;
  unsigned int uData;
  
  // validity check
  *pStr = '\0';
  if (Len <= DecLen)
    return;
  //	if(DecLen == 0 && Len <= 1) return;
  if (DecLen && Len < (DecLen + 2))
    return;
  
  uData = abs(Data);
  if (Data < 0)
    minus = '-';
  else
    minus = ' ';
  
  pStr += Len;
  *pStr-- = '\0';
  i = 0;
  // decimal portion
  while (i < DecLen)
  {
    *pStr-- = uData % 10 + '0';
    uData /= 10;
    i++;
  }
  
  // decimal point
  if (DecLen)
  {
    *pStr-- = '.';
    i++;
  }
  // integer before point.
  *pStr-- = uData % 10 + '0';
  uData /= 10;
  i++;
  // rest integer
  while (i < Len - 1 && uData)
  {
    *pStr-- = uData % 10 + '0';
    uData /= 10;
    i++;
  }
  // sign
  *pStr-- = minus;
  i++;
  // rest blank
  while (i < Len)
  {
    *pStr-- = ' ';
    i++;
  }
}

void uInt2Str(unsigned short uData, unsigned char Len, unsigned char DecLen,  char *pStr)
{
  unsigned char i;
  
  // validity check
  *pStr = '\0';
  if (Len <= DecLen)
    return;
  //	if(DecLen == 0 && Len <= 1) return;
  if (DecLen && Len < (DecLen + 2))
    return;
  
  pStr += Len;
  *pStr-- = '\0';
  i = 0;
  // decimal portion
  while (i < DecLen)
  {
    *pStr-- = uData % 10 + '0';
    uData /= 10;
    i++;
  }
  
  // decimal point
  if (DecLen)
  {
    *pStr-- = '.';
    i++;
  }
  // integer before point.
  *pStr-- = uData % 10 + '0';
  uData /= 10;
  i++;
  // rest integer
  while (i < Len && uData)
  {
    *pStr-- = uData % 10 + '0';
    uData /= 10;
    i++;
  }
  // rest blank
  while (i < Len)
  {
    *pStr-- = ' ';
    i++;
  }
}

// 8x16  高16
void OLED_ShowCharNomAndRev(unsigned char x, unsigned char y, unsigned char chr, unsigned char rev)
{
  unsigned char c = 0, i = 0;
  c = chr - ' '; //得到偏移后的值
  if (x > 128 - 1)
  {
    x = 0;
    y = y + 2;
  } //最多128列
  if (rev == 0)
  {
    OLED_Set_Pos(x, y);
    for (i = 0; i < 8; i++)
      WriteDat(F8X16[c * 16 + i]);
    OLED_Set_Pos(x, y + 1);
    for (i = 0; i < 8; i++)
      WriteDat(F8X16[c * 16 + i + 8]);
  }
  else
  {
    OLED_Set_Pos(x, y);
    for (i = 0; i < 8; i++)
      WriteDat(~F8X16[c * 16 + i]);
    OLED_Set_Pos(x, y + 1);
    for (i = 0; i < 8; i++)
      WriteDat(~F8X16[c * 16 + i + 8]);
  }
}
//-----------------------------------------------------------------------------
//菜单调用这个函数
int PrintHZ(unsigned short ucY, unsigned short ucX,  char *ptr, unsigned short ucRevX, unsigned char ucDispMode, unsigned short ucRevLen, unsigned char ucCodeGen)
{
  unsigned short Len = 0;
  unsigned short i = 0;
  unsigned short j = 0;							 // y用来确定第几个汉字
  unsigned short k = sizeof(Hzk) / sizeof(Hzk[0]); //一共有几个汉字
  unsigned char c1, c2;
  unsigned char revyn;
  unsigned char revynchar;
  
  while (ptr[Len] != 0) //探测字串长度
  {
    Len++;
  }
  while (i < Len)
  {
    c1 = ptr[i];
    c2 = ptr[i + 1];
    
    if (c1 > 128) //是汉字
    {
      for (j = 0; j < k; j++) //找到字模型
      {
        if (c1 == Hzk[j].Index[0] && c2 == Hzk[j].Index[1])
        {
          break;
        }
      }
      
      if (ucDispMode == 1 && (i + ucX) >= ucRevX && (i + ucX) < ucRevX + 2 * ucRevLen)
      {
        revyn = 1;
      }
      else
      {
        revyn = 0;
      }
      
      if (j == k && (c1 != Hzk[j].Index[0] || c2 != Hzk[j].Index[1]))
      {
        
        if ((i + ucX) < 32)
        {
          OLED_ShowCHinese(i * 8 + 8 * ucX, 2 * ucY, (unsigned char *)&Hzk[0].Msk[0], revyn); //实在找不到就打印第一个汉字
        }
      }
      else
      {
        
        if ((i + ucX) < 32)
        {
          OLED_ShowCHinese(i * 8 + 8 * ucX, 2 * ucY, (unsigned char *)&Hzk[j].Msk[0], revyn);
        }
      }
      
      i++; //汉字的话多扫描一次
    }
    else
    {
      if (ucDispMode == 1 && (i + ucX) >= ucRevX && (i + ucX) < ucRevX + ucRevLen)
      {
        revynchar = 1;
      }
      else
      {
        revynchar = 0;
      }
      
      if ((i + ucX) < 32)
      {
        OLED_ShowCharNomAndRev(i * 8 + 8 * ucX, 2 * ucY, ptr[i], revynchar);
      }
    }
    
    i++; //中英文都要扫描
  }
  return 1;
}

//更新Type信息所存Flash
unsigned short Type = 0x1234;
unsigned short Look = 0;
unsigned short SaveCalaCoefficient[16][6];
unsigned short MenuCoefficient[6];
//下面是菜单部分了
char SpaceLine[] = "                "; // string length must as same as M_LCDWIDTH
char NullCode[][2] = {""};
char NullEvent(void) { return TRUE; }
unsigned char StartMenuCnt;
static const REC_FRAME *pCurRec, *pScrTopRec, *pTopRec, *pTmpCurRec; // *pEndRec;
MENU_STA MenuSta = MENU_DISP;
static char CurLine = 0, DigitNum = 0;
static unsigned char ucFlushCount = 0;
static unsigned char StartMenu = 1;
unsigned int Menu1Ms = 0;
unsigned char Menu1Sec = 0;
KEYBUF_FARME keyBuf;

//---------------------------------------------------
RCV_FRAME iMenu;				  //用于显示
SAVEPARA SavePara;				  //需要保存的数据
MAINPARA MainPara;				  //主板采集到的数据
unsigned char iMenuNum = 0;		  //要显示的地址
unsigned char iMenuNumOnlineFlag; //要显示的地址是否在线
unsigned char OnLineNum = 0;	  //统计在线数目 最多16个 最少零个

void LoadSavePara(void)
{
  unsigned int PageAddress = SAVEPAGEADDR;
  unsigned int PageAddressCoe = SAVEPAGEADDRCOE;
  unsigned char i = 0;
  unsigned char j = 0;
  unsigned char k = 0;
  MenuCoefficient[0] = VcoeZ;
  MenuCoefficient[1] = VcoeZ;
  MenuCoefficient[2] = VcoeZ;
  MenuCoefficient[3] = IcoeZ;
  MenuCoefficient[4] = IcoeZ;
  MenuCoefficient[5] = IcoeZ;
  for (i = 0; i < 16; i++) // 0~15个系数最多支持16个从板
  {
    for (j = 0; j < 6; j++)
    {
      SaveCalaCoefficient[i][j] = (*(unsigned short *)(PageAddressCoe + k * 2));
      
      if (j < 3) //电压系数
      {
        if (SaveCalaCoefficient[i][j] > VcoeMax || SaveCalaCoefficient[i][j] < VcoeMin)
        {
          SaveCalaCoefficient[i][j] = VcoeZ;
        }
      }
      else //电流系数
      {
        if (SaveCalaCoefficient[i][j] > IcoeMax || SaveCalaCoefficient[i][j] < IcoeMax)
        {
          SaveCalaCoefficient[i][j] = IcoeZ;
        }
      }
      k++;
    }
  }
  SavePara.Awarm = (*(unsigned short *)(PageAddress + 0 * 2));
  SavePara.Bwarm = (*(unsigned short *)(PageAddress + 1 * 2));
  SavePara.Cwarm = (*(unsigned short *)(PageAddress + 2 * 2));
  SavePara.DcWarm = (*(unsigned short *)(PageAddress + 3 * 2));
  SavePara.DacOut = (*(unsigned short *)(PageAddress + 4 * 2)); ///////
  SavePara.DacVal = (*(unsigned short *)(PageAddress + 5 * 2));
  SavePara.DcHig = (*(unsigned short *)(PageAddress + 6 * 2));
  SavePara.DcLow = (*(unsigned short *)(PageAddress + 7 * 2));
  SavePara.DcRig = (*(unsigned short *)(PageAddress + 8 * 2));
  SavePara.AcHig = (*(unsigned short *)(PageAddress + 9 * 2));
  SavePara.AcLow = (*(unsigned short *)(PageAddress + 10 * 2));
  SavePara.Bdrate = (*(unsigned short *)(PageAddress + 11 * 2));
  SavePara.Addr = (*(unsigned short *)(PageAddress + 12 * 2));
  if (SavePara.Awarm > WarnOnOffMax)
    SavePara.Awarm = WarnOnOffZ;
  if (SavePara.Bwarm > WarnOnOffMax)
    SavePara.Bwarm = WarnOnOffZ;
  if (SavePara.Cwarm > WarnOnOffMax)
    SavePara.Cwarm = WarnOnOffZ;
  if (SavePara.DcWarm > WarnOnOffMax)
    SavePara.DcWarm = WarnOnOffZ;
  if (SavePara.DacOut > WarnOnOffMax)
    SavePara.DacOut = WarnOnOffZ;
  if (SavePara.DacVal > DacValMax)
    SavePara.DacVal = DacValZ;
  if (SavePara.DcHig > DcHigMax || SavePara.DcHig < DcHigMin)
    SavePara.DcHig = DcHigZ;
  if (SavePara.DcLow > DcLowMax || SavePara.DcLow < DcLowMin)
    SavePara.DcLow = DcLowZ;
  if (SavePara.DcRig > DcRigMax || SavePara.DcRig < DcRigMin)
    SavePara.DcRig = DcRigZ;
  if (SavePara.AcHig > AcHigMax || SavePara.AcHig < AcHigMin)
    SavePara.AcHig = AcHigZ;
  if (SavePara.AcLow > AcLowMax || SavePara.AcLow < AcLowMin)
    SavePara.AcLow = AcLowZ;
  if (SavePara.Bdrate > BdrateMax)
    SavePara.Bdrate = BdrateZ;
  if (SavePara.Addr > AddrMax)
    SavePara.Addr = AddrZ;
}
void MX_USART1_UART_InitOwn(unsigned char wBrate)
{ /*
  const unsigned char   *BaudRateCode[] = {
  "4800 ",0
  "9600 ",1
  "14400",2
  "19200",3
  "24000",4
  "28800",5
  "33600",6
  "38400",7
  "115200"8
};
  */
  switch (wBrate)
  {
  case 0:
    huart1.Init.BaudRate = 4800;
    break;
  case 1:
    huart1.Init.BaudRate = 9600;
    break;
  case 2:
    huart1.Init.BaudRate = 14400;
    break;
  case 3:
    huart1.Init.BaudRate = 19200;
    break;
  case 4:
    huart1.Init.BaudRate = 24000;
    break;
  case 5:
    huart1.Init.BaudRate = 28800;
    break;
  case 6:
    huart1.Init.BaudRate = 33600;
    break;
  case 7:
    huart1.Init.BaudRate = 38400;
    break;
  case 8:
    huart1.Init.BaudRate = 115200;
    break;
  default:
    huart1.Init.BaudRate = 9600;
    break;
  }
  huart1.Instance = USART1;
  
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    huart1.Init.BaudRate = 9600;
    HAL_UART_Init(&huart1);
  }
}
uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if ((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0;
  }
  else if ((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1;
  }
  else if ((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2;
  }
  else if ((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3;
  }
  else if ((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4;
  }
  else /*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_5))*/
  {
    sector = FLASH_SECTOR_5;
  }
  
  return sector;
}
char FlashUpdate(void)
{
  
  FLASH_EraseInitTypeDef EraseInitStruct;
  unsigned int FirstSector = 0;
  unsigned int NbOfSectors = 1;
  unsigned int Address = 0;
  uint32_t SectorError = 0;

  MX_USART1_UART_InitOwn(SavePara.Addr);
  
  FirstSector = GetSector(FLASH_USER_START_ADDR);
  
  HAL_FLASH_Unlock(); //解锁flash控制块
  
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
  EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
  EraseInitStruct.Sector = FirstSector;
  EraseInitStruct.NbSectors = NbOfSectors;
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) != HAL_OK)
  {
    Error_Handler();
  }
  
  __HAL_FLASH_DATA_CACHE_DISABLE();
  __HAL_FLASH_INSTRUCTION_CACHE_DISABLE();
  __HAL_FLASH_DATA_CACHE_RESET();
  __HAL_FLASH_INSTRUCTION_CACHE_RESET();
  __HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
  __HAL_FLASH_DATA_CACHE_ENABLE();
  
  Address = FLASH_USER_START_ADDR;
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Address + 0 * 2), SavePara.Awarm);
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Address + 1 * 2), SavePara.Bwarm);
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Address + 2 * 2), SavePara.Cwarm);
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Address + 3 * 2), SavePara.DcWarm);
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Address + 4 * 2), SavePara.DacOut);
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Address + 5 * 2), SavePara.DacVal);
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Address + 6 * 2), SavePara.DcHig);
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Address + 7 * 2), SavePara.DcLow);
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Address + 8 * 2), SavePara.DcRig);
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Address + 9 * 2), SavePara.AcHig);
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Address + 10 * 2), SavePara.AcLow);
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Address + 11 * 2), SavePara.Bdrate);
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (Address + 12 * 2), SavePara.Addr);
  
  HAL_FLASH_Lock(); //给flash上锁
  return 1;
}

////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
const REC_FRAME PageStart[];
const REC_FRAME PageHome[];
const REC_FRAME PageView[];
const REC_FRAME PageSet[];
char *OnlineCode[] = {
  "离线",
  "在线"};
char *OffOnCode[] = {
  "关",
  "开"};

char *OFCode[] = {
  "屏蔽",
  "启用"};

char *SysCode[] = {
  "正常",
  "直流欠压",
  "直流过压"};

char *BaudRateCode[] = {
  "4800 ",
  "9600 ",
  "14400",
  "19200",
  "24000",
  "28800",
  "33600",
  "38400",
  "115200"};



void getKey(KEYTYPE_FRAME *pwhichKey, KEYSTA_FRAME *pKeySta, unsigned int *pkeyNum)
{
  static KEYSTA_FRAME StatusN = KEY_STA_NULL;
  static KEYSTA_FRAME StatusLast = KEY_STA_NULL;
  
  *pkeyNum = keyBuf.keyNum;
  keyBuf.keyNum = 0;
  
  StatusN = keyBuf.ekeySta;
  if (StatusN == KEY_STA_RELEASE && StatusLast == KEY_STA_RELEASE)
    *pKeySta = KEY_STA_NULL;
  else
    *pKeySta = StatusN;
  StatusLast = StatusN;
  
  switch (keyBuf.keyScanCode) //////////////////////////////////////////
  {
  case 1:
    (*pwhichKey) = KEY_ESC;
    break;
  case 2:
    (*pwhichKey) = KEY_DOWN;
    break;
  case 3:
    (*pwhichKey) = KEY_ENTER;
    break;
  case 4:
    (*pwhichKey) = KEY_UP;
    break;
  default:
    (*pwhichKey) = KEY_NULL;
    break;
  }
}

void keyScan(void)
{
  __IO unsigned short keyCodeTmp = 0;
  static unsigned int keyPushCnt = 0;
  static unsigned int keyNumCnt;
  
  if (KEY1)
  {
    keyCodeTmp = 1;
  }
  else if (KEY2)
  {
    keyCodeTmp = 2;
  }
  else if (KEY3)
  {
    keyCodeTmp = 3;
  }
  else if (KEY4)
  {
    keyCodeTmp = 4;
  }
  else
  {
    keyCodeTmp = 0;
  }
  
  if (keyCodeTmp != 0) //是否有按键
  {
    keyPushCnt++; // 连续按键计数
    
    keyNumCnt++; // 区间内按键计数
    
    keyBuf.keyScanCode = keyCodeTmp; //////////////////////////////
    
    if (keyPushCnt == 20)
    {
      keyBuf.ekeySta = KEY_STA_PUSH;
      keyBuf.keyNum = 1;
      return;
    }
    if (keyPushCnt > 15000)
    {
      keyBuf.keyNum++;
      return;
    }
    if (keyPushCnt > 5000)
    {
      if (keyNumCnt > 5)
      {
        keyNumCnt = 0;
        keyBuf.keyNum++;
      }
      return;
    }
    if (keyPushCnt > 500)
    {
      if (keyNumCnt > 100)
      {
        keyBuf.keyNum++;
        keyNumCnt = 0;
      }
      return;
    }
  }
  else //松掉了 没按键了
  {
    keyPushCnt = 0;
    keyNumCnt = 0;
    keyBuf.keyNum = 0;
    if (keyBuf.ekeySta == KEY_STA_PUSH)
    {
      keyBuf.ekeySta = KEY_STA_RELEASE; //如果按下就变松
    }
  }
}

void MenuInit(void)
{
  
  Menu1Sec = 0;
  pCurRec = PageStart;
  pScrTopRec = PageStart + 1;
  pTopRec = PageStart;
  pTmpCurRec = NULL;
  MenuSta = MENU_DISP;
  CurLine = 0;
  DigitNum = 0;
}

// display screen title
void PageTitleDisp(const REC_FRAME *pTopTitleRec, const REC_FRAME *pCurTitleRec, const MENU_STA MenuTitleSta)
{
  const REC_FRAME *pTmpRec, *pRecTmp;
  
  unsigned char ucLine, ucCurInTop;
  
  // first line is fixed
  ucCurInTop = 0;
  
  pTmpRec = pTopTitleRec; //第一条 记录 的首地址  pTmpRec++后即指向下一条记录
  
  while (pTmpRec->RecRange != REC_TOP) //第一条记录的属性 肯定为REC_TOP
  {
    pTmpRec--;
  }
  
  ucLine = 0;
  
  while (ucLine == 0) //行    扫面
  {
    if (pTmpRec == pCurTitleRec && MenuTitleSta == MENU_DISP) //选中反显
    {
      PrintHZ(0, pTmpRec->ucTitleX, pTmpRec->pTitle, pTmpRec->ucTitleRevX, REVERSE, pTmpRec->ucTitleRevLen, CGROM);
    }
    else
    {
      PrintHZ(0, pTmpRec->ucTitleX, pTmpRec->pTitle, pTmpRec->ucTitleRevX, NORMAL, pTmpRec->ucTitleRevLen, CGROM);
    }
    if (pTmpRec == pCurTitleRec)
    {
      ucCurInTop = 1;
    }
    if (pTmpRec->LineRange == LINE_TOPEND || pTmpRec->LineRange == LINE_END) //这行到头了
    {
      ucLine++; //跳出这个while
    }
    
    pTmpRec++; //下一个记录
  }
  
  // line 1 to 6 can scroll, if line has none record to fill, fill in space
  if (ucCurInTop == 0)
  {
    pTmpRec = pTopTitleRec; // current record isn't in first line
  }
  
  ucLine = M_LCDTOPSCRLINE;
  
  while (ucLine <= M_LCDENDSCRLINE)
  {
    // find end record
    if (pTmpRec->LineRange == LINE_TOP || pTmpRec->LineRange == LINE_TOPEND)
    {
      pRecTmp = pTmpRec;
      
      while (pRecTmp->LineRange == LINE_MIDDLE || pRecTmp->LineRange == LINE_TOP)
      {
        pRecTmp++;
      }
      if (pRecTmp->RecRange == REC_END)
      {
        break; //直接跳出 这个循环////////////////////////////////////////
      }
    }
    
    if (pTmpRec == pCurTitleRec && MenuTitleSta == MENU_DISP)
    {
      PrintHZ(ucLine, pTmpRec->ucTitleX, pTmpRec->pTitle, pTmpRec->ucTitleRevX, REVERSE, pTmpRec->ucTitleRevLen, CGROM);
    }
    else
    {
      PrintHZ(ucLine, pTmpRec->ucTitleX, pTmpRec->pTitle, pTmpRec->ucTitleRevX, NORMAL, pTmpRec->ucTitleRevLen, CGROM);
    }
    if (pTmpRec->LineRange == LINE_TOPEND || pTmpRec->LineRange == LINE_END)
    {
      ucLine += 1;
    }
    if (ucLine > M_LCDENDSCRLINE)
    {
      break;
    }
    pTmpRec++;
  }
  
  while (ucLine <= M_LCDENDSCRLINE)
  {
    // Print(pTmpRec->ucTitleX, ucLine, SpaceLine, 0, NORMAL, 0, CGROM);
    PrintHZ(ucLine, pTmpRec->ucTitleX, SpaceLine, 0, NORMAL, 0, CGROM);
    
    ucLine++;
  }
  
  // last line is end record and is fixed
  while (pTmpRec->RecRange != REC_END)
  {
    pTmpRec++;
  }
  while (pTmpRec->LineRange == LINE_MIDDLE || pTmpRec->LineRange == LINE_END)
  {
    pTmpRec--;
  }
  while (ucLine < M_LCDLINE)
  {
    if (pTmpRec == pCurTitleRec && MenuTitleSta == MENU_DISP)
    {
      PrintHZ(ucLine, pTmpRec->ucTitleX, SpaceLine, 0, NORMAL, 0, CGROM);
      PrintHZ(ucLine, pTmpRec->ucTitleX, pTmpRec->pTitle, pTmpRec->ucTitleRevX, REVERSE, pTmpRec->ucTitleRevLen, CGROM);
    }
    else
    {
      PrintHZ(ucLine, pTmpRec->ucTitleX, pTmpRec->pTitle, pTmpRec->ucTitleRevX, NORMAL, pTmpRec->ucTitleRevLen, CGROM);
    }
    if (pTmpRec->LineRange == LINE_TOPEND || pTmpRec->LineRange == LINE_END)
    {
      ucLine++;
    }
    pTmpRec++;
  }
}

void RecVarToPrintStr(const REC_FRAME *pRec,  char *pPrintStr, const REC_FRAME *pCurVarRec, MENU_STA MenuVarSta, unsigned char ucVarDigit)
{
  unsigned char *pStr, ucLoop;
  unsigned char ucVar;
  char scVar;
  unsigned int uiVar;
  int siVar;
  
  if (pRec->ucVarLen >= M_LCDWIDTH)
  {
    *pPrintStr = '\0';
    return;
  }
  
  switch (pRec->VarType)
  {
  case V_CHAR:
    scVar = *((char *)pRec->pVar);
    Char2Str(scVar, pRec->ucVarLen, pRec->ucVarDecLen, pPrintStr);
    break;
  case V_UCHAR:
    ucVar = *((unsigned char *)pRec->pVar);
    uChar2Str(ucVar, pRec->ucVarLen, pRec->ucVarDecLen, pPrintStr);
    break;
  case V_SHORT:
    siVar = *((short *)pRec->pVar);
    Int2Str(siVar, pRec->ucVarLen, pRec->ucVarDecLen, pPrintStr);
    break;
  case V_USHORT:
    uiVar = *((unsigned short *)pRec->pVar);
    uInt2Str(uiVar, pRec->ucVarLen, pRec->ucVarDecLen, pPrintStr);
    break;
    
  case V_STRING:
    pStr = (unsigned char *)pRec->pVar;
    *pPrintStr = *pStr;
    ucLoop = 0;
    while (*pStr != '\0')
    {
      *pPrintStr++ = *pStr++;
      if (ucLoop++ > M_LCDWIDTH)
        break;
    }
    *pPrintStr = '\0';
    break;
    
  case V_ENUM:
    pStr = (unsigned char *)pRec->pEnumStr[*((unsigned char *)pRec->pVar)]; //得到字符串
    
    *pPrintStr = *pStr;
    ucLoop = 0;
    while (*pStr != '\0')
    {
      *pPrintStr++ = *pStr++;
      if (ucLoop++ > M_LCDWIDTH)
        break;
    }
    *pPrintStr = '\0';
    break;
    
  default:
    *pPrintStr = '\0';
    break;
  }
}
// display screen data
//顶记录 当前记录 菜单状态 数字（转化成字符串）
void PageDataDisp(const REC_FRAME *pTopDataRec, const REC_FRAME *pCurDataRec, MENU_STA MenuDataSta, unsigned char ucDigit)
{
  const REC_FRAME *pTmpRec, *pRecTmp;
  static  char ucVarCode[M_LCDWIDTH + 1]; //每一行30个字符
  unsigned char ucLine, ucCurInTop;
  char *pStr;
  
  ucCurInTop = 0;
  pTmpRec = pTopDataRec; //从top开始显示
  while (pTmpRec->RecRange != REC_TOP)
    pTmpRec--; // 第一条如果不是rectop属性指针倒退
  ucLine = 0;
  //第一行记录中数据的显示
  while (ucLine == 0)
  {
    //将记录中数据部分转化为字符串用来显示
    RecVarToPrintStr(pTmpRec, ucVarCode, pCurDataRec, MenuDataSta, ucDigit);
    
    pStr = ucVarCode; //缩写显示的字符串首地址
    
    //记录中数据的显示
    if (pTmpRec == pCurDataRec && MenuDataSta == MENU_EDIT) //记录指针指到了当前记录 且  菜单在编辑状态
    {
      //     记录x                y        字符串地址      反显x         反显       反显长度               反显模式
      PrintHZ(ucLine, pTmpRec->ucVarX, pStr, pTmpRec->ucVarX, REVERSE, pTmpRec->ucVarLen, CGROM);
    }
    else
    {
      PrintHZ(ucLine, pTmpRec->ucVarX, pStr, pTmpRec->ucVarX, NORMAL, 0, CGROM);
    }
    if (pTmpRec == pCurDataRec) // code第一行
    {
      ucCurInTop = 1;
    }
    
    if (pTmpRec->LineRange == LINE_TOPEND || pTmpRec->LineRange == LINE_END)
    {
      ucLine++;
    } //这行数据已经显示完成
    pTmpRec++;
  }
  
  if (ucCurInTop == 0)
    pTmpRec = pTopDataRec;
  ucLine = M_LCDTOPSCRLINE;
  while (ucLine <= M_LCDENDSCRLINE)
  {
    // find end record
    if (pTmpRec->LineRange == LINE_TOP || pTmpRec->LineRange == LINE_TOPEND)
    {
      pRecTmp = pTmpRec;
      while (pRecTmp->LineRange == LINE_MIDDLE || pRecTmp->LineRange == LINE_TOP)
        pRecTmp++;
      if (pRecTmp->RecRange == REC_END)
        break;
    }
    RecVarToPrintStr(pTmpRec, ucVarCode, pCurDataRec, MenuDataSta, ucDigit);
    pStr = ucVarCode;
    if (pTmpRec == pCurDataRec && MenuDataSta == MENU_EDIT)
    {
      PrintHZ(ucLine, pTmpRec->ucVarX, pStr, pTmpRec->ucVarX, REVERSE, pTmpRec->ucVarLen, CGROM);
    }
    else
    {
      PrintHZ(ucLine, pTmpRec->ucVarX, pStr, pTmpRec->ucVarX, NORMAL, 0, CGROM);
    }
    if (pTmpRec->LineRange == LINE_TOPEND || pTmpRec->LineRange == LINE_END)
      ucLine += 1;
    pTmpRec++;
  }
  
  // last line
  ucLine = M_LCDENDSCRLINE + 1;
  while (pTmpRec->RecRange != REC_END)
  {
    pTmpRec++;
  }
  while (pTmpRec->LineRange == LINE_MIDDLE || pTmpRec->LineRange == LINE_END)
    pTmpRec--;
  while (ucLine < M_LCDLINE)
  {
    RecVarToPrintStr(pTmpRec, ucVarCode, pCurDataRec, MenuDataSta, ucDigit);
    pStr = ucVarCode;
    if (pTmpRec == pCurDataRec && MenuDataSta == MENU_EDIT)
    {
      PrintHZ(ucLine, pTmpRec->ucVarX, pStr, pTmpRec->ucVarX, REVERSE, pTmpRec->ucVarLen, CGROM);
    }
    else
    {
      PrintHZ(ucLine, pTmpRec->ucVarX, pStr, pTmpRec->ucVarX, NORMAL, 0, CGROM);
    }
    if (pTmpRec->LineRange == LINE_TOPEND || pTmpRec->LineRange == LINE_END)
      ucLine++;
    pTmpRec++;
  }
}

void MenuCtrl(void)
{
  
  static KEYTYPE_FRAME KeyType = KEY_NULL;	 // see key.h
  static KEYSTA_FRAME KeyStage = KEY_STA_NULL; // see key.h
  static const REC_FRAME *PMenuTopBak = NULL;
  const REC_FRAME *pTmpRec; //
  unsigned int uiKeyNum = 0;
  int siKey = 0;
  long slVarTemp;
  unsigned char *pVuchar;
  char *pVchar;
  unsigned short *pVuint;
  signed short *pVint;
  static unsigned char *pVstr;
  int siMax = 0, siMin = 0;
  
  //----start menu remain 10 seconds
  if (StartMenu)
  {
    Menu1Ms = 0;
    if (Menu1Sec >= STARTMENU_MAX_TIME)
    {
      StartMenu = FALSE;
      Menu1Sec = STARTMENU_MAX_TIME;
      
      MenuSta = MENU_DISP;
      CurLine = 0;
      DigitNum = 0;
      
      //*pCurRec->pEditSta = EDIT_NULL;
      pCurRec = PageHome;
      pScrTopRec = PageHome;
      while (pScrTopRec->LineRange == LINE_TOP || pScrTopRec->LineRange == LINE_MIDDLE)
        pScrTopRec++;
      pScrTopRec++;
      pTopRec = PageHome;
    }
  }
  
  //----if no key operation for greater than M_LCDOFFTIME turn LCD back light off and jump to main menu
  if (Menu1Ms > M_LCDOFFTIME)
  {
    Menu1Ms = 0;
  }
  //----flush title when current record change happened
  if (pTmpCurRec != pCurRec)
  {
    pTmpCurRec = pCurRec;
    
    PageTitleDisp(pScrTopRec, pCurRec, MenuSta);
  }
  
  if (PMenuTopBak != pTopRec)
  {
    PMenuTopBak = pTopRec;
    PageTitleDisp(pScrTopRec, pCurRec, MenuSta);
  }
  
  if (ucFlushCount++ > M_FLUSHCYCLE && pTmpCurRec == pCurRec)
  {
    ucFlushCount = 0;
    PageDataDisp(pScrTopRec, pCurRec, MenuSta, DigitNum); //数据  显示
  }
  
  // get key
  getKey(&KeyType, &KeyStage, &uiKeyNum); //////////////////////////////
  // key not active, RET
  if (KeyStage == KEY_STA_NULL)
    return; //没按键就不用运行下去
  // lcdBklOn();
  Menu1Ms = 0;
  // menu control
  //这下面都是有按键的----------------------------------------------------
  switch (MenuSta)
  {
  case MENU_DISP:
    // wait for key release
    
    if (KeyStage != KEY_STA_RELEASE)
      return;
    
    // down
    if (KeyType == KEY_DOWN)
    {
      
      //显示 在同一行中的多个记录
      while (pCurRec->LineRange != LINE_END && pCurRec->LineRange != LINE_TOPEND) //所在行还有记录
      {
        pCurRec++; //记录表的下一行
        
        //这条记录为连接属性  也到底了
        if (pCurRec->RecType == RECTP_LINK)
          return;
      }
      
      //逐条记录 显示 直到扫描到最后一条记录
      while (pCurRec->RecRange != REC_END)
      {
        pCurRec++; //记录表的下一行
        //
        if (pCurRec->LineRange == LINE_TOP || pCurRec->LineRange == LINE_TOPEND)
        {
          pTmpRec = pCurRec;
          while (pTmpRec->LineRange == LINE_TOP || pTmpRec->LineRange == LINE_MIDDLE)
            pTmpRec++;
          if (pTmpRec->RecRange == REC_END) // 记录表中最后一条记录
          {
            CurLine = M_LCDENDSCRLINE + 1;
          }
          else
          {
            CurLine++;
            if (CurLine > M_LCDENDSCRLINE)
            {
              CurLine = M_LCDENDSCRLINE;
              pScrTopRec++;
              while (pScrTopRec->LineRange != LINE_TOP && pScrTopRec->LineRange != LINE_TOPEND)
                pScrTopRec++;
            }
          }
        }
        if (pCurRec->RecType == RECTP_LINK)
          return;
        if ((pCurRec->LineRange == LINE_END || pCurRec->LineRange == LINE_TOPEND) && pCurRec->RecType != RECTP_NOCUR)
          break;
      }
      
      while (pCurRec->LineRange != LINE_TOP && pCurRec->LineRange != LINE_TOPEND) // line_middle 或 line_end
      {
        if (pCurRec->RecType == RECTP_LINK)
          return;
        else
          pCurRec--;
      }
      
      if (pCurRec->RecRange == REC_END)
      {
        pCurRec--;
        CurLine--;
        return; //记录表里最后一条记录 到底了
      }
      return;
    }
    // up
    if (KeyType == KEY_UP)
    {
      if (pCurRec->RecRange == REC_TOP)
        return; //表中的第一条 到顶了
      while (pCurRec->LineRange != LINE_TOP && pCurRec->LineRange != LINE_TOPEND)
      {
        pCurRec--;
        if (pCurRec->RecType == RECTP_LINK)
          return;
      }
      while (pCurRec->RecRange != REC_TOP)
      {
        pCurRec--;
        if (pCurRec->LineRange == LINE_END || pCurRec->LineRange == LINE_TOPEND)
        {
          pTmpRec = pCurRec;
          while (pTmpRec->LineRange == LINE_END || pTmpRec->LineRange == LINE_MIDDLE)
            pTmpRec--;
          if (pTmpRec->RecRange == REC_TOP)
          {
            CurLine = 0;
          }
          else
          {
            CurLine--;
            if (CurLine < M_LCDTOPSCRLINE)
            {
              CurLine = M_LCDTOPSCRLINE;
              pScrTopRec = pCurRec;
              while (pScrTopRec->LineRange != LINE_TOP && pScrTopRec->LineRange != LINE_TOPEND)
              {
                pScrTopRec--;
              }
            }
          }
        }
        if (pCurRec->RecType == RECTP_LINK)
          return;
        if ((pCurRec->LineRange == LINE_TOP || pCurRec->LineRange == LINE_TOPEND) && pCurRec->RecType != RECTP_NOCUR)
          break;
      }
      pTmpRec = pCurRec;
      while (pTmpRec->LineRange != LINE_END && pTmpRec->LineRange != LINE_TOPEND)
      {
        if (pTmpRec->RecType == RECTP_LINK)
        {
          pCurRec = pTmpRec;
          break;
        }
        pTmpRec++;
      }
      return;
    }
    // enter
    if (KeyType == KEY_ENTER)
    {
      if (pCurRec >= PageStart && pCurRec <= PageStart + 5)
        StartMenu = FALSE;
      
      pTmpRec = pCurRec; // temporary keep pCurRec, in KEY_ENTER code, never change pTmpRec untill end code
      while (1)
      {
        if (pCurRec->RecType == RECTP_NOCUR)
          return; //遇到不能被选中记录属性
        
        if (pCurRec->RecType == RECTP_LINK) //如果是连接属性的记录
        {
          
          (*pCurRec->pEventFunc)();	   //执行当前函数设置频率等函数
          pCurRec = pCurRec->pLinkEnter; //确认 的连接
          pScrTopRec = pCurRec;
          while (pScrTopRec->LineRange == LINE_TOP || pScrTopRec->LineRange == LINE_MIDDLE)
            pScrTopRec++;
          pScrTopRec++;
          pTopRec = pCurRec;
          CurLine = 0;
          pTmpRec = pCurRec;
          while (pTmpRec->LineRange != LINE_END && pTmpRec->LineRange != LINE_TOPEND)
          {
            if (pTmpRec->RecType == RECTP_LINK)
            {
              pCurRec = pTmpRec;
              break;
            }
            pTmpRec++;
          }
          return;
        }
        if (pCurRec->RecType == RECTP_EDIT)
        {
          
          MenuSta = MENU_EDIT;
          //*pCurRec->pEditSta = EDIT_INEDIT;
          if (pCurRec->VarType == V_STRING)
          {
            pVstr = (unsigned char *)pCurRec->pVar;
            DigitNum = 0;
          }
          return;
        }
        if (pCurRec->LineRange == LINE_END || pCurRec->LineRange == LINE_TOPEND)
          break;
        pCurRec++;
      }
      pCurRec = pTmpRec;
      return;
    }
    // escape
    if (KeyType == KEY_ESC)
    {
      if (pCurRec >= PageStart && pCurRec <= PageStart + 5)
      {
        Menu1Sec = STARTMENU_MAX_TIME;
        return;
      }
      pCurRec = pCurRec->pLinkEsc;
      pScrTopRec = pCurRec;
      if (pScrTopRec->RecRange == REC_TOP)
      {
        while (pScrTopRec->LineRange == LINE_TOP || pScrTopRec->LineRange == LINE_MIDDLE)
          pScrTopRec++;
        pScrTopRec++;
      }
      pTopRec = pCurRec;
      CurLine = 0;
      pTmpRec = pCurRec;
      while (pTmpRec->LineRange != LINE_END && pTmpRec->LineRange != LINE_TOPEND)
      {
        if (pTmpRec->RecType == RECTP_LINK)
        {
          pCurRec = pTmpRec;
          break;
        }
        pTmpRec++;
      }
      return;
    }
    break;
  case MENU_EDIT:
    // enter
    if (KeyType == KEY_ENTER)
    {
      if (KeyStage != KEY_STA_RELEASE)
        return; // push active
      while (1)
      {
        
        if (pCurRec->RecType == RECTP_EDIT)
        {
          if (pCurRec->VarType == V_STRING)
          {
            pVstr++;
            DigitNum++;
            if (DigitNum < pCurRec->ucVarLen)
              return;
          }
          //*pCurRec->pEditSta = EDIT_DONE;
          (*pCurRec->pEventFunc)();
        }
        if (pCurRec->LineRange == LINE_END || pCurRec->LineRange == LINE_TOPEND)
          break;
        pCurRec++;
        if (pCurRec->RecType == RECTP_EDIT)
        {
          
          //*pCurRec->pEditSta = EDIT_INEDIT;
          
          if (pCurRec->VarType == V_STRING)
          {
            pVstr = (unsigned char *)pCurRec->pVar;
            DigitNum = 0;
          }
          return;
        }
      }
      while (pCurRec->LineRange != LINE_TOP && pCurRec->LineRange != LINE_TOPEND)
        pCurRec--;
      MenuSta = MENU_DISP;
      return;
    }
    // escape
    if (KeyType == KEY_ESC)
    {
      if (KeyStage != KEY_STA_RELEASE)
        return;
      MenuSta = MENU_DISP;
      //*pCurRec->pEditSta = EDIT_ESC;
      (*pCurRec->pEventFunc)();
      while (pCurRec->LineRange != LINE_TOP && pCurRec->LineRange != LINE_TOPEND)
      {
        pCurRec--;
      }
      return;
    }
    // up or down
    
    if (KeyType == KEY_UP)
      siKey = uiKeyNum;
    else
      siKey = (int)0 - uiKeyNum;
    
    switch (pCurRec->VarType)
    {
    case V_NOP:
      break;
    case V_CHAR:
      pVchar = (char *)pCurRec->pVar;
      siMax = pCurRec->siVarMax;
      siMin = pCurRec->siVarMin;
      slVarTemp = siKey + *pVchar;
      if (slVarTemp > siMax)
        slVarTemp = siMax;
      if (slVarTemp < siMin)
        slVarTemp = siMin;
      *pVchar = slVarTemp;
      break;
    case V_UCHAR:
      pVuchar = (unsigned char *)pCurRec->pVar;
      siMax = pCurRec->siVarMax;
      siMin = pCurRec->siVarMin;
      slVarTemp = (long int)siKey + *pVuchar;
      if (slVarTemp < siMin)
        slVarTemp = siMin;
      if (slVarTemp > siMax)
        slVarTemp = siMax;
      *pVuchar = slVarTemp;
      break;
    case V_SHORT:
      pVint = (signed short *)pCurRec->pVar;
      siMax = pCurRec->siVarMax;
      siMin = pCurRec->siVarMin;
      slVarTemp = siKey + *pVint;
      if (slVarTemp > siMax)
        slVarTemp = siMax;
      if (slVarTemp < siMin)
        slVarTemp = siMin;
      *pVint = slVarTemp;
      break;
    case V_USHORT:
      pVuint = (unsigned short *)pCurRec->pVar;
      siMax = pCurRec->siVarMax;
      siMin = pCurRec->siVarMin;
      slVarTemp = (long int)siKey + *pVuint;
      if (slVarTemp < siMin)
        slVarTemp = siMin;
      if (slVarTemp > siMax)
        slVarTemp = siMax;
      *pVuint = slVarTemp;
      break;
    case V_STRING:
      
    case V_ENUM:
      pVuchar = (unsigned char *)pCurRec->pVar;
      siMax = pCurRec->siVarMax;
      siMin = pCurRec->siVarMin;
      slVarTemp = siKey + *pVuchar;
      if (slVarTemp > siMax)
        slVarTemp = siMax;
      if (slVarTemp < siMin)
        slVarTemp = siMin;
      *pVuchar = slVarTemp;
      break;
      
    default:
      break;
    }
    
    break;
  default:
    break;
  }
}




// 5s停留页面
const REC_FRAME PageStart[] = {
  //*pTitle             ucTitleX  ucTitleRevX   ucTitleRevLen   *pVar                       ucVarX    ucVarLen  ucVarDecLen   VarType    siVarMax               siVarMin             **pEnumStr                                                                                     *pEvent                    RecRange          LineRange         RecType           *pLinkEnter           *pLinkEsc
  { "################",       0,        0,           0,             NULL,                        0,       0,        0,           V_NOP,        0,                    0,                   NULL,                                                                                NullEvent,                       REC_TOP,          LINE_TOPEND,      RECTP_LINK,       PageHome,             PageHome,        },
  { " System Booting ",       0,        0,           0,             NULL,                        0,       0,        0,           V_NOP,        0,                    0,                   NULL,                                                                                NullEvent,                       REC_MIDDLE,       LINE_TOPEND,      RECTP_LINK,       PageHome,             PageHome,        },
  { " Please Wait    ",       0,        0,           0,             NULL,                        0,       0,        0,           V_NOP,        0,                    0,                   NULL,                                                                                NullEvent,                       REC_MIDDLE,       LINE_TOPEND,      RECTP_LINK,       PageHome,             PageHome,        },
  { "################",       0,        0,           0,             NULL,                        0,       0,        0,           V_NOP,        0,                    0,                   NULL,                                                                                NullEvent,                       REC_MIDDLE,       LINE_TOPEND,      RECTP_LINK,       PageHome,             PageHome,        },
  { "################",       0,        0,           0,             NULL,                        0,       0,        0,           V_NOP,        0,                    0,                   NULL,                                                                                NullEvent,                       REC_END,          LINE_TOPEND,      RECTP_LINK,       PageHome,             PageHome,        }
};

//主页    记录表
const REC_FRAME PageHome[] = {
  //*pTitle               ucTitleX     ucTitleRevX  ucTitleRevLen  *pVar                      ucVarX    ucVarLen  ucVarDecLen   VarType     siVarMax              siVarMin             **pEnumStr                                                                                 *pEvent                      RecRange          LineRange         RecType           *pLinkEnter           *pLinkEsc
  {"在线模块数:     ", 0, 0, 10, &OnLineNum, 12, 2, 0, V_UCHAR, 15, 0, NULL, NullEvent, REC_TOP, LINE_TOPEND, RECTP_NOCUR, NULL, PageHome},
  {"直流电压:      V", 0, 0, 5, &MainPara.DcV, 9, 5, 1, V_USHORT, 1000, 0, NULL, NullEvent, REC_MIDDLE, LINE_TOPEND, RECTP_NOCUR, NULL, PageHome},
  {"状态:           ", 0, 0, 5, &MainPara.SysSta, 8, 5, 0, V_ENUM, 1, 0, ( char **)SysCode, NullEvent, REC_MIDDLE, LINE_TOPEND, RECTP_NOCUR, NULL, PageHome},
  {"[模块]  ",         0, 1, 4, NULL, 5, 0, 0, V_NOP, 0, 0, NULL, NullEvent, REC_MIDDLE, LINE_TOP, RECTP_LINK, PageView, PageHome},
  {"  [设置]",         8, 11, 4, NULL, 5, 0, 0, V_NOP, 0, 0, NULL, NullEvent, REC_MIDDLE, LINE_END, RECTP_LINK, PageSet, PageHome},
  {"                ", 0, 0, 0, NULL, 0, 0, 0, V_NOP, 0, 0, NULL, NullEvent, REC_END, LINE_TOPEND, RECTP_LINK, PageHome, PageHome},
};

//详情

const REC_FRAME PageView[] = {
  //*pTitle             ucTitleX     ucTitleRevX    ucTitleRevLen   *pVar                   ucVarX    ucVarLen  ucVarDecLen   VarType      siVarMax             siVarMin           **pEnumStr                                                                                      *pEvent                    RecRange              LineRange     RecType         *pLinkEnter            *pLinkEsc
  {"查看:  [   ]    ", 0, 0, 4, &iMenuNum, 8, 2, 0, V_UCHAR, 0x0f, 0, NULL, NullEvent, REC_TOP, LINE_TOP, RECTP_EDIT, NULL, PageHome},
  {NullCode[0],        0, 0, 1, &iMenuNumOnlineFlag, 12, 4, 0, V_ENUM, 2, 0, ( char **)OnlineCode, NullEvent, REC_MIDDLE, LINE_END, RECTP_NOCUR, NULL, PageHome},
  {"电压A:         V", 0, 0, 5, &iMenu.V1, 9, 5, 0, V_USHORT, 1000, 0, NULL, NullEvent, REC_MIDDLE, LINE_TOPEND, RECTP_NOCUR, NULL, PageHome},
  {"电压B:         V", 0, 0, 5, &iMenu.V2, 9, 5, 0, V_USHORT, 1000, 0, NULL, NullEvent, REC_MIDDLE, LINE_TOPEND, RECTP_NOCUR, NULL, PageHome},
  {"电压C:         V", 0, 0, 5, &iMenu.V3, 9, 5, 0, V_USHORT, 1000, 0, NULL, NullEvent, REC_MIDDLE, LINE_TOPEND, RECTP_NOCUR, NULL, PageHome},
  {"电流A:         A", 0, 0, 5, &iMenu.I1, 9, 5, 0, V_USHORT, 1000, 0, NULL, NullEvent, REC_MIDDLE, LINE_TOPEND, RECTP_NOCUR, NULL, PageHome},
  {"电流B:         A", 0, 0, 5, &iMenu.I2, 9, 5, 0, V_USHORT, 1000, 0, NULL, NullEvent, REC_MIDDLE, LINE_TOPEND, RECTP_NOCUR, NULL, PageHome},
  {"电流C:         A", 0, 0, 5, &iMenu.I3, 9, 5, 0, V_USHORT, 1000, 0, NULL, NullEvent, REC_MIDDLE, LINE_TOPEND, RECTP_NOCUR, NULL, PageHome},
  {"-----[退出]---- ", 0, 6, 4, NULL, 9, 0, 0, V_NOP, 0, 0, NULL, NullEvent, REC_MIDDLE, LINE_TOPEND, RECTP_LINK, PageHome, PageHome},
  {"                 ",0, 0, 0, NULL, 0, 0, 0, V_NOP, 0, 0, NULL, NullEvent, REC_END, LINE_TOPEND, RECTP_NOCUR, NULL, PageHome}
  
};

//通用设置
const REC_FRAME PageSet[] = {
  //*pTitle                ucTitleX     ucTitleRevX     ucTitleRevLen   *pVar                  ucVarX    ucVarLen  ucVarDecLen  VarType       siVarMax              siVarMin            **pEnumStr                                                                                    *pEvent                 RecRange          LineRange        RecType          *pLinkEnter            *pLinkEsc
  {"市电A报警:      ", 0, 0, 5, &SavePara.Awarm, 10, 5, 0, V_ENUM, WarnOnOffMax, WarnOnOffMin, ( char **)OFCode, FlashUpdate, REC_TOP, LINE_TOPEND, RECTP_EDIT, NULL, PageHome},
  {"市电B报警:      ", 0, 0, 5, &SavePara.Bwarm, 10, 5, 0, V_ENUM, WarnOnOffMax, WarnOnOffMin, ( char **)OFCode, FlashUpdate, REC_MIDDLE, LINE_TOPEND, RECTP_EDIT, NULL, PageHome},
  {"市电C报警:      ", 0, 0, 5, &SavePara.Cwarm, 10, 5, 0, V_ENUM, WarnOnOffMax, WarnOnOffMin, ( char **)OFCode, FlashUpdate, REC_MIDDLE, LINE_TOPEND, RECTP_EDIT, NULL, PageHome},
  {"直流报警:       ", 0, 0, 5, &SavePara.DcWarm, 10, 5, 0, V_ENUM, WarnOnOffMax, WarnOnOffMin, ( char **)OFCode, FlashUpdate, REC_MIDDLE, LINE_TOPEND, RECTP_EDIT, NULL, PageHome},
  {"欠压补偿:       ", 0, 0, 5, &SavePara.DacOut, 10, 5, 0, V_ENUM, WarnOnOffMax, WarnOnOffMin, ( char **)OFCode, FlashUpdate, REC_MIDDLE, LINE_TOPEND, RECTP_EDIT, NULL, PageHome},
  {"补偿电压:      V", 0, 0, 5, &SavePara.DacVal, 9, 5, 1, V_UCHAR, DacValMax, DacValMin, NULL, FlashUpdate, REC_MIDDLE, LINE_TOPEND, RECTP_EDIT, NULL, PageHome},
  {"直流过压:      V", 0, 0, 5, &SavePara.DcHig, 9, 5, 1, V_USHORT, DcHigMax, DcHigMin, NULL, FlashUpdate, REC_MIDDLE, LINE_TOPEND, RECTP_EDIT, NULL, PageHome},
  {"直流欠压:      V", 0, 0, 5, &SavePara.DcLow, 9, 5, 1, V_USHORT, DcLowMax, DcLowMin, NULL, FlashUpdate, REC_MIDDLE, LINE_TOPEND, RECTP_EDIT, NULL, PageHome},
  {"直流触发:      V", 0, 0, 5, &SavePara.DcRig, 9, 5, 1, V_USHORT, DcRigMax, DcRigMin, NULL, FlashUpdate, REC_MIDDLE, LINE_TOPEND, RECTP_EDIT, NULL, PageHome},
  {"交流过压:      V", 0, 0, 5, &SavePara.AcHig, 9, 5, 0, V_USHORT, AcHigMax, AcHigMin, NULL, FlashUpdate, REC_MIDDLE, LINE_TOPEND, RECTP_EDIT, NULL, PageHome},
  {"交流欠压:      V", 0, 0, 5, &SavePara.AcLow, 9, 5, 0, V_UCHAR, AcLowMin, AcLowMin, NULL, FlashUpdate, REC_MIDDLE, LINE_TOPEND, RECTP_EDIT, NULL, PageHome},
  {"波特率:         ", 0, 0, 5, &SavePara.Bdrate, 10, 5, 0, V_ENUM, BdrateMax, BdrateMin, ( char **)BaudRateCode, FlashUpdate, REC_MIDDLE, LINE_TOPEND, RECTP_EDIT, NULL, PageHome},
  {"地址:           ", 0, 0, 4, &SavePara.Addr, 10, 3, 0, V_UCHAR, AddrMax, AddrMin, NULL, FlashUpdate, REC_MIDDLE, LINE_TOPEND, RECTP_EDIT, NULL, PageHome},
  {"-----[退出]---- ", 0, 6, 2, NULL, 0, 0, 0, V_NOP, 0, 0, NULL, NullEvent, REC_MIDDLE, LINE_TOPEND, RECTP_LINK, PageHome, PageHome},
  {"                ", 0, 0, 0, NULL, 0, 0, 0, V_NOP, 0, 0, NULL, NullEvent, REC_END, LINE_TOPEND, RECTP_NOCUR, NULL, PageHome}
  
};

; ModuleID = 'test_module'
source_filename = "test_module"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function to add two integers
define i32 @add(i32 %a, i32 %b) {
entry:
  %sum = add i32 %a, %b
  ret i32 %sum
}

; Function to subtract two integers
define i32 @subtract(i32 %a, i32 %b) {
entry:
  %diff = sub i32 %a, %b
  ret i32 %diff
}

; Function to multiply two integers
define i32 @multiply(i32 %a, i32 %b) {
entry:
  %product = mul i32 %a, %b
  ret i32 %product
}

; Main function
define i32 @main() {
entry:
  %result1 = call i32 @add(i32 10, i32 20)
  %result2 = call i32 @subtract(i32 50, i32 30)
  %result3 = call i32 @multiply(i32 5, i32 6)
  ret i32 0
}

; Declaration of an external function
declare void @external_func()
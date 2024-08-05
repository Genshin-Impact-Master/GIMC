; ModuleID = 'lib/newlib.c'
source_filename = "lib/newlib.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.timeval = type { i64, i64 }
%struct.__va_list_tag = type { i32, i32, ptr, ptr }

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@.str.2 = private unnamed_addr constant [3 x i8] c"%a\00", align 1
@.str.3 = private unnamed_addr constant [4 x i8] c"%d:\00", align 1
@.str.4 = private unnamed_addr constant [4 x i8] c" %d\00", align 1
@.str.5 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.6 = private unnamed_addr constant [4 x i8] c" %a\00", align 1
@stdout = external global ptr, align 8
@_sysy_l1 = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_idx = dso_local global i32 0, align 4
@_sysy_start = dso_local global %struct.timeval zeroinitializer, align 8
@_sysy_end = dso_local global %struct.timeval zeroinitializer, align 8
@_sysy_l2 = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_us = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_s = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_m = dso_local global [1024 x i32] zeroinitializer, align 16
@_sysy_h = dso_local global [1024 x i32] zeroinitializer, align 16

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @getint() #0 {
entry:
  %t = alloca i32, align 4
  %call = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str, ptr noundef %t)
  %0 = load i32, ptr %t, align 4
  ret i32 %0
}

declare i32 @__isoc99_scanf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @getch() #0 {
entry:
  %c = alloca i8, align 1
  %call = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str.1, ptr noundef %c)
  %0 = load i8, ptr %c, align 1
  %conv = sext i8 %0 to i32
  ret i32 %conv
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local float @getfloat() #0 {
entry:
  %n = alloca float, align 4
  %call = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str.2, ptr noundef %n)
  %0 = load float, ptr %n, align 4
  ret float %0
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @getarray(ptr noundef %a) #0 {
entry:
  %a.addr = alloca ptr, align 8
  %n = alloca i32, align 4
  %i = alloca i32, align 4
  store ptr %a, ptr %a.addr, align 8
  %call = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str, ptr noundef %n)
  store i32 0, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, ptr %i, align 4
  %1 = load i32, ptr %n, align 4
  %cmp = icmp slt i32 %0, %1
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %2 = load ptr, ptr %a.addr, align 8
  %3 = load i32, ptr %i, align 4
  %idxprom = sext i32 %3 to i64
  %arrayidx = getelementptr inbounds i32, ptr %2, i64 %idxprom
  %call1 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str, ptr noundef %arrayidx)
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %4 = load i32, ptr %i, align 4
  %inc = add nsw i32 %4, 1
  store i32 %inc, ptr %i, align 4
  br label %for.cond, !llvm.loop !6

for.end:                                          ; preds = %for.cond
  %5 = load i32, ptr %n, align 4
  ret i32 %5
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @getfarray(ptr noundef %a) #0 {
entry:
  %a.addr = alloca ptr, align 8
  %n = alloca i32, align 4
  %i = alloca i32, align 4
  store ptr %a, ptr %a.addr, align 8
  %call = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str, ptr noundef %n)
  store i32 0, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, ptr %i, align 4
  %1 = load i32, ptr %n, align 4
  %cmp = icmp slt i32 %0, %1
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %2 = load ptr, ptr %a.addr, align 8
  %3 = load i32, ptr %i, align 4
  %idxprom = sext i32 %3 to i64
  %arrayidx = getelementptr inbounds float, ptr %2, i64 %idxprom
  %call1 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str.2, ptr noundef %arrayidx)
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %4 = load i32, ptr %i, align 4
  %inc = add nsw i32 %4, 1
  store i32 %inc, ptr %i, align 4
  br label %for.cond, !llvm.loop !8

for.end:                                          ; preds = %for.cond
  %5 = load i32, ptr %n, align 4
  ret i32 %5
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @putint(i32 noundef %a) #0 {
entry:
  %a.addr = alloca i32, align 4
  store i32 %a, ptr %a.addr, align 4
  %0 = load i32, ptr %a.addr, align 4
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %0)
  ret void
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @putch(i32 noundef %a) #0 {
entry:
  %a.addr = alloca i32, align 4
  store i32 %a, ptr %a.addr, align 4
  %0 = load i32, ptr %a.addr, align 4
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %0)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @putarray(i32 noundef %n, ptr noundef %a) #0 {
entry:
  %n.addr = alloca i32, align 4
  %a.addr = alloca ptr, align 8
  %i = alloca i32, align 4
  store i32 %n, ptr %n.addr, align 4
  store ptr %a, ptr %a.addr, align 8
  %0 = load i32, ptr %n.addr, align 4
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str.3, i32 noundef %0)
  store i32 0, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %1 = load i32, ptr %i, align 4
  %2 = load i32, ptr %n.addr, align 4
  %cmp = icmp slt i32 %1, %2
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %3 = load ptr, ptr %a.addr, align 8
  %4 = load i32, ptr %i, align 4
  %idxprom = sext i32 %4 to i64
  %arrayidx = getelementptr inbounds i32, ptr %3, i64 %idxprom
  %5 = load i32, ptr %arrayidx, align 4
  %call1 = call i32 (ptr, ...) @printf(ptr noundef @.str.4, i32 noundef %5)
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %6 = load i32, ptr %i, align 4
  %inc = add nsw i32 %6, 1
  store i32 %inc, ptr %i, align 4
  br label %for.cond, !llvm.loop !9

for.end:                                          ; preds = %for.cond
  %call2 = call i32 (ptr, ...) @printf(ptr noundef @.str.5)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @putfloat(float noundef %a) #0 {
entry:
  %a.addr = alloca float, align 4
  store float %a, ptr %a.addr, align 4
  %0 = load float, ptr %a.addr, align 4
  %conv = fpext float %0 to double
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str.2, double noundef %conv)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @putfarray(i32 noundef %n, ptr noundef %a) #0 {
entry:
  %n.addr = alloca i32, align 4
  %a.addr = alloca ptr, align 8
  %i = alloca i32, align 4
  store i32 %n, ptr %n.addr, align 4
  store ptr %a, ptr %a.addr, align 8
  %0 = load i32, ptr %n.addr, align 4
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str.3, i32 noundef %0)
  store i32 0, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %1 = load i32, ptr %i, align 4
  %2 = load i32, ptr %n.addr, align 4
  %cmp = icmp slt i32 %1, %2
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %3 = load ptr, ptr %a.addr, align 8
  %4 = load i32, ptr %i, align 4
  %idxprom = sext i32 %4 to i64
  %arrayidx = getelementptr inbounds float, ptr %3, i64 %idxprom
  %5 = load float, ptr %arrayidx, align 4
  %conv = fpext float %5 to double
  %call1 = call i32 (ptr, ...) @printf(ptr noundef @.str.6, double noundef %conv)
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %6 = load i32, ptr %i, align 4
  %inc = add nsw i32 %6, 1
  store i32 %inc, ptr %i, align 4
  br label %for.cond, !llvm.loop !10

for.end:                                          ; preds = %for.cond
  %call2 = call i32 (ptr, ...) @printf(ptr noundef @.str.5)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @putf(ptr noundef %a, ...) #0 {
entry:
  %a.addr = alloca ptr, align 8
  %args = alloca [1 x %struct.__va_list_tag], align 16
  store ptr %a, ptr %a.addr, align 8
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], ptr %args, i64 0, i64 0
  call void @llvm.va_start.p0(ptr %arraydecay)
  %0 = load ptr, ptr @stdout, align 8
  %1 = load ptr, ptr %a.addr, align 8
  %arraydecay1 = getelementptr inbounds [1 x %struct.__va_list_tag], ptr %args, i64 0, i64 0
  %call = call i32 @vfprintf(ptr noundef %0, ptr noundef %1, ptr noundef %arraydecay1) #4
  %arraydecay2 = getelementptr inbounds [1 x %struct.__va_list_tag], ptr %args, i64 0, i64 0
  call void @llvm.va_end.p0(ptr %arraydecay2)
  ret void
}

; Function Attrs: nocallback nofree nosync nounwind willreturn
declare void @llvm.va_start.p0(ptr) #2

; Function Attrs: nounwind
declare i32 @vfprintf(ptr noundef, ptr noundef, ptr noundef) #3

; Function Attrs: nocallback nofree nosync nounwind willreturn
declare void @llvm.va_end.p0(ptr) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_sysy_starttime(i32 noundef %lineno) #0 {
entry:
  %lineno.addr = alloca i32, align 4
  store i32 %lineno, ptr %lineno.addr, align 4
  %0 = load i32, ptr %lineno.addr, align 4
  %1 = load i32, ptr @_sysy_idx, align 4
  %idxprom = sext i32 %1 to i64
  %arrayidx = getelementptr inbounds [1024 x i32], ptr @_sysy_l1, i64 0, i64 %idxprom
  store i32 %0, ptr %arrayidx, align 4
  %call = call i32 @gettimeofday(ptr noundef @_sysy_start, ptr noundef null) #4
  ret void
}

; Function Attrs: nounwind
declare i32 @gettimeofday(ptr noundef, ptr noundef) #3

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_sysy_stoptime(i32 noundef %lineno) #0 {
entry:
  %lineno.addr = alloca i32, align 4
  store i32 %lineno, ptr %lineno.addr, align 4
  %call = call i32 @gettimeofday(ptr noundef @_sysy_end, ptr noundef null) #4
  %0 = load i32, ptr %lineno.addr, align 4
  %1 = load i32, ptr @_sysy_idx, align 4
  %idxprom = sext i32 %1 to i64
  %arrayidx = getelementptr inbounds [1024 x i32], ptr @_sysy_l2, i64 0, i64 %idxprom
  store i32 %0, ptr %arrayidx, align 4
  %2 = load i64, ptr @_sysy_end, align 8
  %3 = load i64, ptr @_sysy_start, align 8
  %sub = sub nsw i64 %2, %3
  %mul = mul nsw i64 1000000, %sub
  %4 = load i64, ptr getelementptr inbounds (%struct.timeval, ptr @_sysy_end, i32 0, i32 1), align 8
  %add = add nsw i64 %mul, %4
  %5 = load i64, ptr getelementptr inbounds (%struct.timeval, ptr @_sysy_start, i32 0, i32 1), align 8
  %sub1 = sub nsw i64 %add, %5
  %6 = load i32, ptr @_sysy_idx, align 4
  %idxprom2 = sext i32 %6 to i64
  %arrayidx3 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %idxprom2
  %7 = load i32, ptr %arrayidx3, align 4
  %conv = sext i32 %7 to i64
  %add4 = add nsw i64 %conv, %sub1
  %conv5 = trunc i64 %add4 to i32
  store i32 %conv5, ptr %arrayidx3, align 4
  %8 = load i32, ptr @_sysy_idx, align 4
  %idxprom6 = sext i32 %8 to i64
  %arrayidx7 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %idxprom6
  %9 = load i32, ptr %arrayidx7, align 4
  %div = sdiv i32 %9, 1000000
  %10 = load i32, ptr @_sysy_idx, align 4
  %idxprom8 = sext i32 %10 to i64
  %arrayidx9 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %idxprom8
  %11 = load i32, ptr %arrayidx9, align 4
  %add10 = add nsw i32 %11, %div
  store i32 %add10, ptr %arrayidx9, align 4
  %12 = load i32, ptr @_sysy_idx, align 4
  %idxprom11 = sext i32 %12 to i64
  %arrayidx12 = getelementptr inbounds [1024 x i32], ptr @_sysy_us, i64 0, i64 %idxprom11
  %13 = load i32, ptr %arrayidx12, align 4
  %rem = srem i32 %13, 1000000
  store i32 %rem, ptr %arrayidx12, align 4
  %14 = load i32, ptr @_sysy_idx, align 4
  %idxprom13 = sext i32 %14 to i64
  %arrayidx14 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %idxprom13
  %15 = load i32, ptr %arrayidx14, align 4
  %div15 = sdiv i32 %15, 60
  %16 = load i32, ptr @_sysy_idx, align 4
  %idxprom16 = sext i32 %16 to i64
  %arrayidx17 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %idxprom16
  %17 = load i32, ptr %arrayidx17, align 4
  %add18 = add nsw i32 %17, %div15
  store i32 %add18, ptr %arrayidx17, align 4
  %18 = load i32, ptr @_sysy_idx, align 4
  %idxprom19 = sext i32 %18 to i64
  %arrayidx20 = getelementptr inbounds [1024 x i32], ptr @_sysy_s, i64 0, i64 %idxprom19
  %19 = load i32, ptr %arrayidx20, align 4
  %rem21 = srem i32 %19, 60
  store i32 %rem21, ptr %arrayidx20, align 4
  %20 = load i32, ptr @_sysy_idx, align 4
  %idxprom22 = sext i32 %20 to i64
  %arrayidx23 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %idxprom22
  %21 = load i32, ptr %arrayidx23, align 4
  %div24 = sdiv i32 %21, 60
  %22 = load i32, ptr @_sysy_idx, align 4
  %idxprom25 = sext i32 %22 to i64
  %arrayidx26 = getelementptr inbounds [1024 x i32], ptr @_sysy_h, i64 0, i64 %idxprom25
  %23 = load i32, ptr %arrayidx26, align 4
  %add27 = add nsw i32 %23, %div24
  store i32 %add27, ptr %arrayidx26, align 4
  %24 = load i32, ptr @_sysy_idx, align 4
  %idxprom28 = sext i32 %24 to i64
  %arrayidx29 = getelementptr inbounds [1024 x i32], ptr @_sysy_m, i64 0, i64 %idxprom28
  %25 = load i32, ptr %arrayidx29, align 4
  %rem30 = srem i32 %25, 60
  store i32 %rem30, ptr %arrayidx29, align 4
  %26 = load i32, ptr @_sysy_idx, align 4
  %inc = add nsw i32 %26, 1
  store i32 %inc, ptr @_sysy_idx, align 4
  ret void
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nocallback nofree nosync nounwind willreturn }
attributes #3 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 19.0.0git (https://github.com/llvm/llvm-project.git fe47e8ff3ae7fc8975eaade6bfa6679737c28b93)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}

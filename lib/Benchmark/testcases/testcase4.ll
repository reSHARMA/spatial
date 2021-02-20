; ModuleID = 'testcase4.cpp'
source_filename = "testcase4.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@x = dso_local global i32* null, align 8, !dbg !0
@y = dso_local global i32* null, align 8, !dbg !6
@w = dso_local global i32* null, align 8, !dbg !10
@p = dso_local global i32** null, align 8, !dbg !12
@q = dso_local global i32** null, align 8, !dbg !15
@a = dso_local global i32 0, align 4, !dbg !17
@b = dso_local global i32 0, align 4, !dbg !19
@c = dso_local global i32 0, align 4, !dbg !21

; Function Attrs: noinline norecurse uwtable
define dso_local i32 @main() #0 !dbg !27 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32** @x, i32*** @p, align 8, !dbg !30
  store i32* @a, i32** @x, align 8, !dbg !31
  %2 = load i32**, i32*** @p, align 8, !dbg !32
  %3 = load i32*, i32** @x, align 8, !dbg !33
  call void @_Z12MustPointsToIPPiS0_EvT_T0_(i32** %2, i32* %3), !dbg !34
  %4 = load i32*, i32** @x, align 8, !dbg !35
  %5 = load i32, i32* @a, align 4, !dbg !36
  call void @_Z12MustPointsToIPiiEvT_T0_(i32* %4, i32 %5), !dbg !37
  %6 = load i32, i32* @a, align 4, !dbg !38
  switch i32 %6, label %17 [
    i32 1, label %7
    i32 2, label %10
    i32 3, label %13
    i32 5, label %16
  ], !dbg !39

7:                                                ; preds = %0
  store i32* @b, i32** @x, align 8, !dbg !40
  %8 = load i32*, i32** @x, align 8, !dbg !42
  %9 = load i32, i32* @b, align 4, !dbg !43
  call void @_Z12MustPointsToIPiiEvT_T0_(i32* %8, i32 %9), !dbg !44
  br label %20, !dbg !45

10:                                               ; preds = %0
  store i32* @c, i32** @x, align 8, !dbg !46
  %11 = load i32*, i32** @x, align 8, !dbg !47
  %12 = load i32, i32* @c, align 4, !dbg !48
  call void @_Z12MustPointsToIPiiEvT_T0_(i32* %11, i32 %12), !dbg !49
  br label %20, !dbg !50

13:                                               ; preds = %0
  store i32* @a, i32** @y, align 8, !dbg !51
  %14 = load i32*, i32** @y, align 8, !dbg !52
  %15 = load i32, i32* @a, align 4, !dbg !53
  call void @_Z12MustPointsToIPiiEvT_T0_(i32* %14, i32 %15), !dbg !54
  br label %20, !dbg !55

16:                                               ; preds = %0
  br label %20, !dbg !56

17:                                               ; preds = %0
  store i32* @b, i32** @y, align 8, !dbg !57
  %18 = load i32*, i32** @y, align 8, !dbg !58
  %19 = load i32, i32* @b, align 4, !dbg !59
  call void @_Z12MustPointsToIPiiEvT_T0_(i32* %18, i32 %19), !dbg !60
  br label %20, !dbg !61

20:                                               ; preds = %17, %16, %13, %10, %7
  %21 = load i32**, i32*** @p, align 8, !dbg !62
  %22 = load i32*, i32** @x, align 8, !dbg !63
  call void @_Z12MustPointsToIPPiS0_EvT_T0_(i32** %21, i32* %22), !dbg !64
  %23 = load i32*, i32** @x, align 8, !dbg !65
  %24 = load i32, i32* @a, align 4, !dbg !66
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %23, i32 %24), !dbg !67
  %25 = load i32*, i32** @x, align 8, !dbg !68
  %26 = load i32, i32* @b, align 4, !dbg !69
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %25, i32 %26), !dbg !70
  %27 = load i32*, i32** @x, align 8, !dbg !71
  %28 = load i32, i32* @c, align 4, !dbg !72
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %27, i32 %28), !dbg !73
  %29 = load i32*, i32** @y, align 8, !dbg !74
  %30 = load i32, i32* @a, align 4, !dbg !75
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %29, i32 %30), !dbg !76
  %31 = load i32*, i32** @y, align 8, !dbg !77
  %32 = load i32, i32* @b, align 4, !dbg !78
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %31, i32 %32), !dbg !79
  %33 = load i32*, i32** @w, align 8, !dbg !80
  %34 = load i32**, i32*** @p, align 8, !dbg !81
  store i32* %33, i32** %34, align 8, !dbg !82
  %35 = load i32*, i32** @y, align 8, !dbg !83
  %36 = load i32, i32* @a, align 4, !dbg !84
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %35, i32 %36), !dbg !85
  %37 = load i32*, i32** @y, align 8, !dbg !86
  %38 = load i32, i32* @b, align 4, !dbg !87
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %37, i32 %38), !dbg !88
  %39 = load i32, i32* %1, align 4, !dbg !89
  ret i32 %39, !dbg !89
}

declare dso_local void @_Z12MustPointsToIPPiS0_EvT_T0_(i32**, i32*) #1

declare dso_local void @_Z12MustPointsToIPiiEvT_T0_(i32*, i32) #1

declare dso_local void @_Z11MayPointsToIPiiEvT_T0_(i32*, i32) #1

attributes #0 = { noinline norecurse uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!23, !24, !25}
!llvm.ident = !{!26}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "x", scope: !2, file: !3, line: 3, type: !8, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "testcase4.cpp", directory: "/home/mehul/Rnd_Project/testcases")
!4 = !{}
!5 = !{!0, !6, !10, !12, !15, !17, !19, !21}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "y", scope: !2, file: !3, line: 3, type: !8, isLocal: false, isDefinition: true)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!10 = !DIGlobalVariableExpression(var: !11, expr: !DIExpression())
!11 = distinct !DIGlobalVariable(name: "w", scope: !2, file: !3, line: 3, type: !8, isLocal: false, isDefinition: true)
!12 = !DIGlobalVariableExpression(var: !13, expr: !DIExpression())
!13 = distinct !DIGlobalVariable(name: "p", scope: !2, file: !3, line: 3, type: !14, isLocal: false, isDefinition: true)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64)
!15 = !DIGlobalVariableExpression(var: !16, expr: !DIExpression())
!16 = distinct !DIGlobalVariable(name: "q", scope: !2, file: !3, line: 3, type: !14, isLocal: false, isDefinition: true)
!17 = !DIGlobalVariableExpression(var: !18, expr: !DIExpression())
!18 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 3, type: !9, isLocal: false, isDefinition: true)
!19 = !DIGlobalVariableExpression(var: !20, expr: !DIExpression())
!20 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 3, type: !9, isLocal: false, isDefinition: true)
!21 = !DIGlobalVariableExpression(var: !22, expr: !DIExpression())
!22 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 3, type: !9, isLocal: false, isDefinition: true)
!23 = !{i32 7, !"Dwarf Version", i32 4}
!24 = !{i32 2, !"Debug Info Version", i32 3}
!25 = !{i32 1, !"wchar_size", i32 4}
!26 = !{!"clang version 10.0.0-4ubuntu1 "}
!27 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 4, type: !28, scopeLine: 4, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!28 = !DISubroutineType(types: !29)
!29 = !{!9}
!30 = !DILocation(line: 5, column: 7, scope: !27)
!31 = !DILocation(line: 6, column: 4, scope: !27)
!32 = !DILocation(line: 8, column: 15, scope: !27)
!33 = !DILocation(line: 8, column: 17, scope: !27)
!34 = !DILocation(line: 8, column: 2, scope: !27)
!35 = !DILocation(line: 9, column: 15, scope: !27)
!36 = !DILocation(line: 9, column: 17, scope: !27)
!37 = !DILocation(line: 9, column: 2, scope: !27)
!38 = !DILocation(line: 11, column: 9, scope: !27)
!39 = !DILocation(line: 11, column: 2, scope: !27)
!40 = !DILocation(line: 13, column: 6, scope: !41)
!41 = distinct !DILexicalBlock(scope: !27, file: !3, line: 11, column: 11)
!42 = !DILocation(line: 14, column: 17, scope: !41)
!43 = !DILocation(line: 14, column: 19, scope: !41)
!44 = !DILocation(line: 14, column: 4, scope: !41)
!45 = !DILocation(line: 15, column: 4, scope: !41)
!46 = !DILocation(line: 17, column: 6, scope: !41)
!47 = !DILocation(line: 18, column: 17, scope: !41)
!48 = !DILocation(line: 18, column: 19, scope: !41)
!49 = !DILocation(line: 18, column: 4, scope: !41)
!50 = !DILocation(line: 19, column: 4, scope: !41)
!51 = !DILocation(line: 21, column: 6, scope: !41)
!52 = !DILocation(line: 22, column: 17, scope: !41)
!53 = !DILocation(line: 22, column: 19, scope: !41)
!54 = !DILocation(line: 22, column: 4, scope: !41)
!55 = !DILocation(line: 23, column: 4, scope: !41)
!56 = !DILocation(line: 25, column: 4, scope: !41)
!57 = !DILocation(line: 27, column: 6, scope: !41)
!58 = !DILocation(line: 28, column: 17, scope: !41)
!59 = !DILocation(line: 28, column: 19, scope: !41)
!60 = !DILocation(line: 28, column: 4, scope: !41)
!61 = !DILocation(line: 29, column: 4, scope: !41)
!62 = !DILocation(line: 31, column: 15, scope: !27)
!63 = !DILocation(line: 31, column: 17, scope: !27)
!64 = !DILocation(line: 31, column: 2, scope: !27)
!65 = !DILocation(line: 32, column: 14, scope: !27)
!66 = !DILocation(line: 32, column: 16, scope: !27)
!67 = !DILocation(line: 32, column: 2, scope: !27)
!68 = !DILocation(line: 33, column: 14, scope: !27)
!69 = !DILocation(line: 33, column: 16, scope: !27)
!70 = !DILocation(line: 33, column: 2, scope: !27)
!71 = !DILocation(line: 34, column: 14, scope: !27)
!72 = !DILocation(line: 34, column: 16, scope: !27)
!73 = !DILocation(line: 34, column: 2, scope: !27)
!74 = !DILocation(line: 35, column: 14, scope: !27)
!75 = !DILocation(line: 35, column: 16, scope: !27)
!76 = !DILocation(line: 35, column: 2, scope: !27)
!77 = !DILocation(line: 36, column: 14, scope: !27)
!78 = !DILocation(line: 36, column: 16, scope: !27)
!79 = !DILocation(line: 36, column: 2, scope: !27)
!80 = !DILocation(line: 37, column: 7, scope: !27)
!81 = !DILocation(line: 37, column: 3, scope: !27)
!82 = !DILocation(line: 37, column: 5, scope: !27)
!83 = !DILocation(line: 39, column: 14, scope: !27)
!84 = !DILocation(line: 39, column: 16, scope: !27)
!85 = !DILocation(line: 39, column: 2, scope: !27)
!86 = !DILocation(line: 40, column: 14, scope: !27)
!87 = !DILocation(line: 40, column: 16, scope: !27)
!88 = !DILocation(line: 40, column: 2, scope: !27)
!89 = !DILocation(line: 42, column: 1, scope: !27)

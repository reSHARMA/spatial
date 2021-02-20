; ModuleID = 'testcase6.cpp'
source_filename = "testcase6.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@p = dso_local global i32** null, align 8, !dbg !0
@q = dso_local global i32** null, align 8, !dbg !6
@r = dso_local global i32** null, align 8, !dbg !11
@a = dso_local global i32* null, align 8, !dbg !13
@b = dso_local global i32* null, align 8, !dbg !15
@c = dso_local global i32* null, align 8, !dbg !17
@d = dso_local global i32* null, align 8, !dbg !19
@e = dso_local global i32* null, align 8, !dbg !21
@m = dso_local global i32 0, align 4, !dbg !23

; Function Attrs: noinline norecurse uwtable
define dso_local i32 @main() #0 !dbg !29 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  br label %2, !dbg !32

2:                                                ; preds = %19, %0
  %3 = load i32**, i32*** @q, align 8, !dbg !33
  %4 = load i32*, i32** @b, align 8, !dbg !35
  call void @_Z11MayPointsToIPPiS0_EvT_T0_(i32** %3, i32* %4), !dbg !36
  store i32** @a, i32*** @r, align 8, !dbg !37
  %5 = load i32**, i32*** @r, align 8, !dbg !38
  %6 = load i32*, i32** @a, align 8, !dbg !39
  call void @_Z12MustPointsToIPPiS0_EvT_T0_(i32** %5, i32* %6), !dbg !40
  %7 = load i32**, i32*** @q, align 8, !dbg !41
  store i32* @m, i32** %7, align 8, !dbg !42
  %8 = load i32*, i32** @b, align 8, !dbg !43
  %9 = load i32, i32* @m, align 4, !dbg !44
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %8, i32 %9), !dbg !45
  %10 = load i32, i32* @m, align 4, !dbg !46
  %11 = icmp ne i32 %10, 0, !dbg !46
  br i1 %11, label %12, label %15, !dbg !48

12:                                               ; preds = %2
  store i32** @b, i32*** @q, align 8, !dbg !49
  %13 = load i32**, i32*** @q, align 8, !dbg !51
  %14 = load i32*, i32** @b, align 8, !dbg !52
  call void @_Z12MustPointsToIPPiS0_EvT_T0_(i32** %13, i32* %14), !dbg !53
  br label %16, !dbg !54

15:                                               ; preds = %2
  br label %20, !dbg !55

16:                                               ; preds = %12
  %17 = load i32**, i32*** @q, align 8, !dbg !57
  %18 = load i32*, i32** @b, align 8, !dbg !58
  call void @_Z11MayPointsToIPPiS0_EvT_T0_(i32** %17, i32* %18), !dbg !59
  br label %19, !dbg !60

19:                                               ; preds = %16
  br i1 true, label %2, label %20, !dbg !60, !llvm.loop !61

20:                                               ; preds = %19, %15
  %21 = load i32**, i32*** @q, align 8, !dbg !63
  %22 = load i32*, i32** @b, align 8, !dbg !64
  call void @_Z11MayPointsToIPPiS0_EvT_T0_(i32** %21, i32* %22), !dbg !65
  %23 = load i32*, i32** @b, align 8, !dbg !66
  %24 = load i32, i32* @m, align 4, !dbg !67
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %23, i32 %24), !dbg !68
  %25 = load i32**, i32*** @r, align 8, !dbg !69
  %26 = load i32*, i32** @a, align 8, !dbg !70
  call void @_Z11MayPointsToIPPiS0_EvT_T0_(i32** %25, i32* %26), !dbg !71
  %27 = load i32**, i32*** @p, align 8, !dbg !72
  %28 = load i32*, i32** %27, align 8, !dbg !73
  store i32* %28, i32** @e, align 8, !dbg !74
  store i32** @e, i32*** @q, align 8, !dbg !75
  %29 = load i32**, i32*** @q, align 8, !dbg !76
  %30 = load i32*, i32** @e, align 8, !dbg !77
  call void @_Z12MustPointsToIPPiS0_EvT_T0_(i32** %29, i32* %30), !dbg !78
  %31 = load i32, i32* %1, align 4, !dbg !79
  ret i32 %31, !dbg !79
}

declare dso_local void @_Z11MayPointsToIPPiS0_EvT_T0_(i32**, i32*) #1

declare dso_local void @_Z12MustPointsToIPPiS0_EvT_T0_(i32**, i32*) #1

declare dso_local void @_Z11MayPointsToIPiiEvT_T0_(i32*, i32) #1

attributes #0 = { noinline norecurse uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!25, !26, !27}
!llvm.ident = !{!28}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "p", scope: !2, file: !3, line: 3, type: !8, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "testcase6.cpp", directory: "/home/mehul/Rnd_Project/testcases")
!4 = !{}
!5 = !{!0, !6, !11, !13, !15, !17, !19, !21, !23}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "q", scope: !2, file: !3, line: 3, type: !8, isLocal: false, isDefinition: true)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !DIGlobalVariableExpression(var: !12, expr: !DIExpression())
!12 = distinct !DIGlobalVariable(name: "r", scope: !2, file: !3, line: 3, type: !8, isLocal: false, isDefinition: true)
!13 = !DIGlobalVariableExpression(var: !14, expr: !DIExpression())
!14 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 4, type: !9, isLocal: false, isDefinition: true)
!15 = !DIGlobalVariableExpression(var: !16, expr: !DIExpression())
!16 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 4, type: !9, isLocal: false, isDefinition: true)
!17 = !DIGlobalVariableExpression(var: !18, expr: !DIExpression())
!18 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 4, type: !9, isLocal: false, isDefinition: true)
!19 = !DIGlobalVariableExpression(var: !20, expr: !DIExpression())
!20 = distinct !DIGlobalVariable(name: "d", scope: !2, file: !3, line: 4, type: !9, isLocal: false, isDefinition: true)
!21 = !DIGlobalVariableExpression(var: !22, expr: !DIExpression())
!22 = distinct !DIGlobalVariable(name: "e", scope: !2, file: !3, line: 4, type: !9, isLocal: false, isDefinition: true)
!23 = !DIGlobalVariableExpression(var: !24, expr: !DIExpression())
!24 = distinct !DIGlobalVariable(name: "m", scope: !2, file: !3, line: 5, type: !10, isLocal: false, isDefinition: true)
!25 = !{i32 7, !"Dwarf Version", i32 4}
!26 = !{i32 2, !"Debug Info Version", i32 3}
!27 = !{i32 1, !"wchar_size", i32 4}
!28 = !{!"clang version 10.0.0-4ubuntu1 "}
!29 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 6, type: !30, scopeLine: 7, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!30 = !DISubroutineType(types: !31)
!31 = !{!10}
!32 = !DILocation(line: 8, column: 5, scope: !29)
!33 = !DILocation(line: 10, column: 21, scope: !34)
!34 = distinct !DILexicalBlock(scope: !29, file: !3, line: 9, column: 5)
!35 = !DILocation(line: 10, column: 23, scope: !34)
!36 = !DILocation(line: 10, column: 9, scope: !34)
!37 = !DILocation(line: 11, column: 11, scope: !34)
!38 = !DILocation(line: 12, column: 22, scope: !34)
!39 = !DILocation(line: 12, column: 24, scope: !34)
!40 = !DILocation(line: 12, column: 9, scope: !34)
!41 = !DILocation(line: 14, column: 10, scope: !34)
!42 = !DILocation(line: 14, column: 12, scope: !34)
!43 = !DILocation(line: 15, column: 21, scope: !34)
!44 = !DILocation(line: 15, column: 23, scope: !34)
!45 = !DILocation(line: 15, column: 9, scope: !34)
!46 = !DILocation(line: 16, column: 13, scope: !47)
!47 = distinct !DILexicalBlock(scope: !34, file: !3, line: 16, column: 13)
!48 = !DILocation(line: 16, column: 13, scope: !34)
!49 = !DILocation(line: 18, column: 15, scope: !50)
!50 = distinct !DILexicalBlock(scope: !47, file: !3, line: 17, column: 9)
!51 = !DILocation(line: 19, column: 26, scope: !50)
!52 = !DILocation(line: 19, column: 28, scope: !50)
!53 = !DILocation(line: 19, column: 13, scope: !50)
!54 = !DILocation(line: 20, column: 9, scope: !50)
!55 = !DILocation(line: 23, column: 13, scope: !56)
!56 = distinct !DILexicalBlock(scope: !47, file: !3, line: 22, column: 9)
!57 = !DILocation(line: 25, column: 21, scope: !34)
!58 = !DILocation(line: 25, column: 23, scope: !34)
!59 = !DILocation(line: 25, column: 9, scope: !34)
!60 = !DILocation(line: 26, column: 5, scope: !34)
!61 = distinct !{!61, !32, !62}
!62 = !DILocation(line: 26, column: 15, scope: !29)
!63 = !DILocation(line: 27, column: 17, scope: !29)
!64 = !DILocation(line: 27, column: 19, scope: !29)
!65 = !DILocation(line: 27, column: 5, scope: !29)
!66 = !DILocation(line: 28, column: 17, scope: !29)
!67 = !DILocation(line: 28, column: 19, scope: !29)
!68 = !DILocation(line: 28, column: 5, scope: !29)
!69 = !DILocation(line: 29, column: 17, scope: !29)
!70 = !DILocation(line: 29, column: 19, scope: !29)
!71 = !DILocation(line: 29, column: 5, scope: !29)
!72 = !DILocation(line: 30, column: 10, scope: !29)
!73 = !DILocation(line: 30, column: 9, scope: !29)
!74 = !DILocation(line: 30, column: 7, scope: !29)
!75 = !DILocation(line: 31, column: 7, scope: !29)
!76 = !DILocation(line: 32, column: 18, scope: !29)
!77 = !DILocation(line: 32, column: 20, scope: !29)
!78 = !DILocation(line: 32, column: 5, scope: !29)
!79 = !DILocation(line: 33, column: 1, scope: !29)

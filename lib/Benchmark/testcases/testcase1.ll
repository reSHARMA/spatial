; ModuleID = 'testcase1.cpp'
source_filename = "testcase1.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@p = dso_local global i32*** null, align 8, !dbg !0
@q = dso_local global i32** null, align 8, !dbg !6
@a = dso_local global i32** null, align 8, !dbg !11
@b = dso_local global i32** null, align 8, !dbg !13
@c = dso_local global i32* null, align 8, !dbg !15
@m = dso_local global i32* null, align 8, !dbg !17
@n = dso_local global i32* null, align 8, !dbg !19
@d = dso_local global i32 0, align 4, !dbg !21

; Function Attrs: noinline norecurse uwtable
define dso_local i32 @main() #0 !dbg !28 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32* @d, i32** @m, align 8, !dbg !31
  store i32** @c, i32*** @b, align 8, !dbg !32
  store i32** @c, i32*** @a, align 8, !dbg !33
  %2 = load i32**, i32*** @a, align 8, !dbg !34
  %3 = icmp ne i32** %2, null, !dbg !34
  br i1 %3, label %4, label %15, !dbg !36

4:                                                ; preds = %0
  store i32*** @a, i32**** @p, align 8, !dbg !37
  %5 = load i32***, i32**** @p, align 8, !dbg !39
  %6 = load i32**, i32*** @a, align 8, !dbg !40
  call void @_Z12MustPointsToIPPPiS1_EvT_T0_(i32*** %5, i32** %6), !dbg !41
  %7 = load i32***, i32**** @p, align 8, !dbg !42
  %8 = load i32**, i32*** @b, align 8, !dbg !43
  call void @_Z15DoesNotPointsToIPPPiS1_EvT_T0_(i32*** %7, i32** %8), !dbg !44
  store i32** @c, i32*** @q, align 8, !dbg !45
  %9 = load i32**, i32*** @q, align 8, !dbg !46
  %10 = load i32*, i32** @c, align 8, !dbg !47
  call void @_Z12MustPointsToIPPiS0_EvT_T0_(i32** %9, i32* %10), !dbg !48
  %11 = load i32**, i32*** @q, align 8, !dbg !49
  %12 = load i32*, i32** @m, align 8, !dbg !50
  call void @_Z15DoesNotPointsToIPPiS0_EvT_T0_(i32** %11, i32* %12), !dbg !51
  %13 = load i32**, i32*** @q, align 8, !dbg !52
  %14 = load i32*, i32** @n, align 8, !dbg !53
  call void @_Z15DoesNotPointsToIPPiS0_EvT_T0_(i32** %13, i32* %14), !dbg !54
  br label %26, !dbg !55

15:                                               ; preds = %0
  store i32*** @b, i32**** @p, align 8, !dbg !56
  %16 = load i32***, i32**** @p, align 8, !dbg !58
  %17 = load i32**, i32*** @b, align 8, !dbg !59
  call void @_Z12MustPointsToIPPPiS1_EvT_T0_(i32*** %16, i32** %17), !dbg !60
  %18 = load i32***, i32**** @p, align 8, !dbg !61
  %19 = load i32**, i32*** @a, align 8, !dbg !62
  call void @_Z15DoesNotPointsToIPPPiS1_EvT_T0_(i32*** %18, i32** %19), !dbg !63
  store i32** @c, i32*** @q, align 8, !dbg !64
  %20 = load i32**, i32*** @q, align 8, !dbg !65
  %21 = load i32*, i32** @c, align 8, !dbg !66
  call void @_Z12MustPointsToIPPiS0_EvT_T0_(i32** %20, i32* %21), !dbg !67
  %22 = load i32**, i32*** @q, align 8, !dbg !68
  %23 = load i32*, i32** @m, align 8, !dbg !69
  call void @_Z15DoesNotPointsToIPPiS0_EvT_T0_(i32** %22, i32* %23), !dbg !70
  %24 = load i32**, i32*** @q, align 8, !dbg !71
  %25 = load i32*, i32** @n, align 8, !dbg !72
  call void @_Z15DoesNotPointsToIPPiS0_EvT_T0_(i32** %24, i32* %25), !dbg !73
  br label %26

26:                                               ; preds = %15, %4
  %27 = load i32***, i32**** @p, align 8, !dbg !74
  %28 = load i32**, i32*** @a, align 8, !dbg !75
  call void @_Z11MayPointsToIPPPiS1_EvT_T0_(i32*** %27, i32** %28), !dbg !76
  %29 = load i32***, i32**** @p, align 8, !dbg !77
  %30 = load i32**, i32*** @b, align 8, !dbg !78
  call void @_Z11MayPointsToIPPPiS1_EvT_T0_(i32*** %29, i32** %30), !dbg !79
  %31 = load i32**, i32*** @q, align 8, !dbg !80
  %32 = load i32*, i32** @c, align 8, !dbg !81
  call void @_Z12MustPointsToIPPiS0_EvT_T0_(i32** %31, i32* %32), !dbg !82
  %33 = load i32**, i32*** @q, align 8, !dbg !83
  %34 = load i32*, i32** @m, align 8, !dbg !84
  call void @_Z15DoesNotPointsToIPPiS0_EvT_T0_(i32** %33, i32* %34), !dbg !85
  %35 = load i32**, i32*** @q, align 8, !dbg !86
  %36 = load i32*, i32** @n, align 8, !dbg !87
  call void @_Z15DoesNotPointsToIPPiS0_EvT_T0_(i32** %35, i32* %36), !dbg !88
  %37 = load i32*, i32** @m, align 8, !dbg !89
  %38 = load i32**, i32*** @a, align 8, !dbg !90
  store i32* %37, i32** %38, align 8, !dbg !91
  %39 = load i32*, i32** @c, align 8, !dbg !92
  %40 = load i32, i32* @d, align 4, !dbg !93
  call void @_Z12MustPointsToIPiiEvT_T0_(i32* %39, i32 %40), !dbg !94
  %41 = load i32**, i32*** @b, align 8, !dbg !95
  %42 = load i32*, i32** %41, align 8, !dbg !96
  store i32* %42, i32** @n, align 8, !dbg !97
  %43 = load i32*, i32** @n, align 8, !dbg !98
  %44 = load i32, i32* @d, align 4, !dbg !99
  call void @_Z12MustPointsToIPiiEvT_T0_(i32* %43, i32 %44), !dbg !100
  %45 = load i32***, i32**** @p, align 8, !dbg !101
  store i32** @n, i32*** %45, align 8, !dbg !102
  %46 = load i32**, i32*** @a, align 8, !dbg !103
  %47 = load i32*, i32** @n, align 8, !dbg !104
  call void @_Z11MayPointsToIPPiS0_EvT_T0_(i32** %46, i32* %47), !dbg !105
  %48 = load i32**, i32*** @b, align 8, !dbg !106
  %49 = load i32*, i32** @n, align 8, !dbg !107
  call void @_Z11MayPointsToIPPiS0_EvT_T0_(i32** %48, i32* %49), !dbg !108
  %50 = load i32**, i32*** @a, align 8, !dbg !109
  %51 = load i32*, i32** @c, align 8, !dbg !110
  call void @_Z11MayPointsToIPPiS0_EvT_T0_(i32** %50, i32* %51), !dbg !111
  %52 = load i32**, i32*** @b, align 8, !dbg !112
  %53 = load i32*, i32** @c, align 8, !dbg !113
  call void @_Z11MayPointsToIPPiS0_EvT_T0_(i32** %52, i32* %53), !dbg !114
  %54 = load i32**, i32*** @a, align 8, !dbg !115
  %55 = load i32*, i32** @m, align 8, !dbg !116
  call void @_Z15DoesNotPointsToIPPiS0_EvT_T0_(i32** %54, i32* %55), !dbg !117
  %56 = load i32**, i32*** @b, align 8, !dbg !118
  %57 = load i32*, i32** @m, align 8, !dbg !119
  call void @_Z15DoesNotPointsToIPPiS0_EvT_T0_(i32** %56, i32* %57), !dbg !120
  %58 = load i32, i32* %1, align 4, !dbg !121
  ret i32 %58, !dbg !121
}

declare dso_local void @_Z12MustPointsToIPPPiS1_EvT_T0_(i32***, i32**) #1

declare dso_local void @_Z15DoesNotPointsToIPPPiS1_EvT_T0_(i32***, i32**) #1

declare dso_local void @_Z12MustPointsToIPPiS0_EvT_T0_(i32**, i32*) #1

declare dso_local void @_Z15DoesNotPointsToIPPiS0_EvT_T0_(i32**, i32*) #1

declare dso_local void @_Z11MayPointsToIPPPiS1_EvT_T0_(i32***, i32**) #1

declare dso_local void @_Z12MustPointsToIPiiEvT_T0_(i32*, i32) #1

declare dso_local void @_Z11MayPointsToIPPiS0_EvT_T0_(i32**, i32*) #1

attributes #0 = { noinline norecurse uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!24, !25, !26}
!llvm.ident = !{!27}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "p", scope: !2, file: !3, line: 2, type: !23, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "testcase1.cpp", directory: "/home/mehul/Rnd_Project/testcases")
!4 = !{}
!5 = !{!0, !6, !11, !13, !15, !17, !19, !21}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "q", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !DIGlobalVariableExpression(var: !12, expr: !DIExpression())
!12 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!13 = !DIGlobalVariableExpression(var: !14, expr: !DIExpression())
!14 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!15 = !DIGlobalVariableExpression(var: !16, expr: !DIExpression())
!16 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!17 = !DIGlobalVariableExpression(var: !18, expr: !DIExpression())
!18 = distinct !DIGlobalVariable(name: "m", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!19 = !DIGlobalVariableExpression(var: !20, expr: !DIExpression())
!20 = distinct !DIGlobalVariable(name: "n", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!21 = !DIGlobalVariableExpression(var: !22, expr: !DIExpression())
!22 = distinct !DIGlobalVariable(name: "d", scope: !2, file: !3, line: 2, type: !10, isLocal: false, isDefinition: true)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64)
!24 = !{i32 7, !"Dwarf Version", i32 4}
!25 = !{i32 2, !"Debug Info Version", i32 3}
!26 = !{i32 1, !"wchar_size", i32 4}
!27 = !{!"clang version 10.0.0-4ubuntu1 "}
!28 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 3, type: !29, scopeLine: 3, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!29 = !DISubroutineType(types: !30)
!30 = !{!10}
!31 = !DILocation(line: 5, column: 7, scope: !28)
!32 = !DILocation(line: 6, column: 11, scope: !28)
!33 = !DILocation(line: 6, column: 7, scope: !28)
!34 = !DILocation(line: 7, column: 8, scope: !35)
!35 = distinct !DILexicalBlock(scope: !28, file: !3, line: 7, column: 8)
!36 = !DILocation(line: 7, column: 8, scope: !28)
!37 = !DILocation(line: 9, column: 11, scope: !38)
!38 = distinct !DILexicalBlock(scope: !35, file: !3, line: 8, column: 5)
!39 = !DILocation(line: 10, column: 22, scope: !38)
!40 = !DILocation(line: 10, column: 24, scope: !38)
!41 = !DILocation(line: 10, column: 9, scope: !38)
!42 = !DILocation(line: 11, column: 25, scope: !38)
!43 = !DILocation(line: 11, column: 27, scope: !38)
!44 = !DILocation(line: 11, column: 9, scope: !38)
!45 = !DILocation(line: 13, column: 11, scope: !38)
!46 = !DILocation(line: 14, column: 22, scope: !38)
!47 = !DILocation(line: 14, column: 24, scope: !38)
!48 = !DILocation(line: 14, column: 9, scope: !38)
!49 = !DILocation(line: 15, column: 25, scope: !38)
!50 = !DILocation(line: 15, column: 27, scope: !38)
!51 = !DILocation(line: 15, column: 9, scope: !38)
!52 = !DILocation(line: 16, column: 25, scope: !38)
!53 = !DILocation(line: 16, column: 27, scope: !38)
!54 = !DILocation(line: 16, column: 9, scope: !38)
!55 = !DILocation(line: 17, column: 5, scope: !38)
!56 = !DILocation(line: 20, column: 11, scope: !57)
!57 = distinct !DILexicalBlock(scope: !35, file: !3, line: 19, column: 5)
!58 = !DILocation(line: 21, column: 22, scope: !57)
!59 = !DILocation(line: 21, column: 24, scope: !57)
!60 = !DILocation(line: 21, column: 9, scope: !57)
!61 = !DILocation(line: 22, column: 25, scope: !57)
!62 = !DILocation(line: 22, column: 27, scope: !57)
!63 = !DILocation(line: 22, column: 9, scope: !57)
!64 = !DILocation(line: 24, column: 11, scope: !57)
!65 = !DILocation(line: 25, column: 22, scope: !57)
!66 = !DILocation(line: 25, column: 24, scope: !57)
!67 = !DILocation(line: 25, column: 9, scope: !57)
!68 = !DILocation(line: 26, column: 25, scope: !57)
!69 = !DILocation(line: 26, column: 27, scope: !57)
!70 = !DILocation(line: 26, column: 9, scope: !57)
!71 = !DILocation(line: 27, column: 25, scope: !57)
!72 = !DILocation(line: 27, column: 27, scope: !57)
!73 = !DILocation(line: 27, column: 9, scope: !57)
!74 = !DILocation(line: 31, column: 17, scope: !28)
!75 = !DILocation(line: 31, column: 19, scope: !28)
!76 = !DILocation(line: 31, column: 5, scope: !28)
!77 = !DILocation(line: 32, column: 17, scope: !28)
!78 = !DILocation(line: 32, column: 19, scope: !28)
!79 = !DILocation(line: 32, column: 5, scope: !28)
!80 = !DILocation(line: 33, column: 18, scope: !28)
!81 = !DILocation(line: 33, column: 20, scope: !28)
!82 = !DILocation(line: 33, column: 5, scope: !28)
!83 = !DILocation(line: 34, column: 21, scope: !28)
!84 = !DILocation(line: 34, column: 23, scope: !28)
!85 = !DILocation(line: 34, column: 5, scope: !28)
!86 = !DILocation(line: 35, column: 21, scope: !28)
!87 = !DILocation(line: 35, column: 23, scope: !28)
!88 = !DILocation(line: 35, column: 5, scope: !28)
!89 = !DILocation(line: 38, column: 7, scope: !28)
!90 = !DILocation(line: 38, column: 3, scope: !28)
!91 = !DILocation(line: 38, column: 5, scope: !28)
!92 = !DILocation(line: 39, column: 18, scope: !28)
!93 = !DILocation(line: 39, column: 20, scope: !28)
!94 = !DILocation(line: 39, column: 5, scope: !28)
!95 = !DILocation(line: 41, column: 7, scope: !28)
!96 = !DILocation(line: 41, column: 6, scope: !28)
!97 = !DILocation(line: 41, column: 4, scope: !28)
!98 = !DILocation(line: 42, column: 15, scope: !28)
!99 = !DILocation(line: 42, column: 17, scope: !28)
!100 = !DILocation(line: 42, column: 2, scope: !28)
!101 = !DILocation(line: 44, column: 3, scope: !28)
!102 = !DILocation(line: 44, column: 4, scope: !28)
!103 = !DILocation(line: 45, column: 14, scope: !28)
!104 = !DILocation(line: 45, column: 16, scope: !28)
!105 = !DILocation(line: 45, column: 2, scope: !28)
!106 = !DILocation(line: 46, column: 14, scope: !28)
!107 = !DILocation(line: 46, column: 16, scope: !28)
!108 = !DILocation(line: 46, column: 2, scope: !28)
!109 = !DILocation(line: 47, column: 17, scope: !28)
!110 = !DILocation(line: 47, column: 19, scope: !28)
!111 = !DILocation(line: 47, column: 5, scope: !28)
!112 = !DILocation(line: 48, column: 14, scope: !28)
!113 = !DILocation(line: 48, column: 16, scope: !28)
!114 = !DILocation(line: 48, column: 2, scope: !28)
!115 = !DILocation(line: 49, column: 21, scope: !28)
!116 = !DILocation(line: 49, column: 23, scope: !28)
!117 = !DILocation(line: 49, column: 5, scope: !28)
!118 = !DILocation(line: 50, column: 21, scope: !28)
!119 = !DILocation(line: 50, column: 23, scope: !28)
!120 = !DILocation(line: 50, column: 5, scope: !28)
!121 = !DILocation(line: 51, column: 1, scope: !28)

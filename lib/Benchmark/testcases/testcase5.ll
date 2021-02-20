; ModuleID = 'testcase5.cpp'
source_filename = "testcase5.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@p = dso_local global i32** null, align 8, !dbg !0
@q = dso_local global i32** null, align 8, !dbg !6
@x = dso_local global i32* null, align 8, !dbg !11
@y = dso_local global i32* null, align 8, !dbg !13
@a = dso_local global i32 0, align 4, !dbg !15
@b = dso_local global i32 0, align 4, !dbg !17
@c = dso_local global i32 0, align 4, !dbg !19
@d = dso_local global i32 0, align 4, !dbg !21
@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1

; Function Attrs: noinline norecurse uwtable
define dso_local i32 @main() #0 !dbg !27 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !30, metadata !DIExpression()), !dbg !31
  store i32** @x, i32*** @p, align 8, !dbg !32
  store i32** @y, i32*** @q, align 8, !dbg !33
  %3 = load i32**, i32*** @p, align 8, !dbg !34
  %4 = load i32*, i32** @x, align 8, !dbg !35
  call void @_Z12MustPointsToIPPiS0_EvT_T0_(i32** %3, i32* %4), !dbg !36
  %5 = load i32**, i32*** @q, align 8, !dbg !37
  %6 = load i32*, i32** @y, align 8, !dbg !38
  call void @_Z12MustPointsToIPPiS0_EvT_T0_(i32** %5, i32* %6), !dbg !39
  store i32 40, i32* @d, align 4, !dbg !40
  %7 = load i32, i32* @b, align 4, !dbg !41
  %8 = icmp ne i32 %7, 0, !dbg !41
  br i1 %8, label %9, label %15, !dbg !43

9:                                                ; preds = %0
  %10 = load i32**, i32*** @q, align 8, !dbg !44
  store i32* @a, i32** %10, align 8, !dbg !46
  store i32* @b, i32** @x, align 8, !dbg !47
  %11 = load i32*, i32** @y, align 8, !dbg !48
  %12 = load i32, i32* @a, align 4, !dbg !49
  call void @_Z12MustPointsToIPiiEvT_T0_(i32* %11, i32 %12), !dbg !50
  %13 = load i32*, i32** @x, align 8, !dbg !51
  %14 = load i32, i32* @b, align 4, !dbg !52
  call void @_Z12MustPointsToIPiiEvT_T0_(i32* %13, i32 %14), !dbg !53
  br label %21, !dbg !54

15:                                               ; preds = %0
  %16 = load i32**, i32*** @p, align 8, !dbg !55
  store i32* @a, i32** %16, align 8, !dbg !57
  store i32* @b, i32** @y, align 8, !dbg !58
  %17 = load i32*, i32** @x, align 8, !dbg !59
  %18 = load i32, i32* @a, align 4, !dbg !60
  call void @_Z12MustPointsToIPiiEvT_T0_(i32* %17, i32 %18), !dbg !61
  %19 = load i32*, i32** @y, align 8, !dbg !62
  %20 = load i32, i32* @b, align 4, !dbg !63
  call void @_Z12MustPointsToIPiiEvT_T0_(i32* %19, i32 %20), !dbg !64
  br label %21

21:                                               ; preds = %15, %9
  %22 = load i32*, i32** @x, align 8, !dbg !65
  %23 = load i32, i32* @a, align 4, !dbg !66
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %22, i32 %23), !dbg !67
  %24 = load i32*, i32** @x, align 8, !dbg !68
  %25 = load i32, i32* @b, align 4, !dbg !69
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %24, i32 %25), !dbg !70
  %26 = load i32*, i32** @y, align 8, !dbg !71
  %27 = load i32, i32* @a, align 4, !dbg !72
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %26, i32 %27), !dbg !73
  %28 = load i32*, i32** @y, align 8, !dbg !74
  %29 = load i32, i32* @b, align 4, !dbg !75
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %28, i32 %29), !dbg !76
  %30 = load i32*, i32** @y, align 8, !dbg !77
  store i32* %30, i32** @x, align 8, !dbg !78
  %31 = load i32*, i32** @x, align 8, !dbg !79
  %32 = load i32, i32* @a, align 4, !dbg !80
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %31, i32 %32), !dbg !81
  %33 = load i32*, i32** @x, align 8, !dbg !82
  %34 = load i32, i32* @b, align 4, !dbg !83
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %33, i32 %34), !dbg !84
  %35 = load i32*, i32** @y, align 8, !dbg !85
  %36 = load i32, i32* @a, align 4, !dbg !86
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %35, i32 %36), !dbg !87
  %37 = load i32*, i32** @y, align 8, !dbg !88
  %38 = load i32, i32* @b, align 4, !dbg !89
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %37, i32 %38), !dbg !90
  %39 = load i32, i32* @b, align 4, !dbg !91
  store i32 %39, i32* @a, align 4, !dbg !92
  %40 = load i32**, i32*** @p, align 8, !dbg !93
  %41 = load i32*, i32** %40, align 8, !dbg !94
  store i32 30, i32* %41, align 4, !dbg !95
  %42 = load i32*, i32** @x, align 8, !dbg !96
  store i32 40, i32* %42, align 4, !dbg !97
  %43 = load i32, i32* %2, align 4, !dbg !98
  %44 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32 %43), !dbg !99
  %45 = load i32, i32* %1, align 4, !dbg !100
  ret i32 %45, !dbg !100
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local void @_Z12MustPointsToIPPiS0_EvT_T0_(i32**, i32*) #2

declare dso_local void @_Z12MustPointsToIPiiEvT_T0_(i32*, i32) #2

declare dso_local void @_Z11MayPointsToIPiiEvT_T0_(i32*, i32) #2

declare dso_local i32 @printf(i8*, ...) #2

attributes #0 = { noinline norecurse uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!23, !24, !25}
!llvm.ident = !{!26}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "p", scope: !2, file: !3, line: 3, type: !8, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "testcase5.cpp", directory: "/home/mehul/Rnd_Project/testcases")
!4 = !{}
!5 = !{!0, !6, !11, !13, !15, !17, !19, !21}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "q", scope: !2, file: !3, line: 3, type: !8, isLocal: false, isDefinition: true)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !DIGlobalVariableExpression(var: !12, expr: !DIExpression())
!12 = distinct !DIGlobalVariable(name: "x", scope: !2, file: !3, line: 4, type: !9, isLocal: false, isDefinition: true)
!13 = !DIGlobalVariableExpression(var: !14, expr: !DIExpression())
!14 = distinct !DIGlobalVariable(name: "y", scope: !2, file: !3, line: 4, type: !9, isLocal: false, isDefinition: true)
!15 = !DIGlobalVariableExpression(var: !16, expr: !DIExpression())
!16 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 5, type: !10, isLocal: false, isDefinition: true)
!17 = !DIGlobalVariableExpression(var: !18, expr: !DIExpression())
!18 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 5, type: !10, isLocal: false, isDefinition: true)
!19 = !DIGlobalVariableExpression(var: !20, expr: !DIExpression())
!20 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 5, type: !10, isLocal: false, isDefinition: true)
!21 = !DIGlobalVariableExpression(var: !22, expr: !DIExpression())
!22 = distinct !DIGlobalVariable(name: "d", scope: !2, file: !3, line: 5, type: !10, isLocal: false, isDefinition: true)
!23 = !{i32 7, !"Dwarf Version", i32 4}
!24 = !{i32 2, !"Debug Info Version", i32 3}
!25 = !{i32 1, !"wchar_size", i32 4}
!26 = !{!"clang version 10.0.0-4ubuntu1 "}
!27 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 6, type: !28, scopeLine: 7, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!28 = !DISubroutineType(types: !29)
!29 = !{!10}
!30 = !DILocalVariable(name: "e", scope: !27, file: !3, line: 9, type: !10)
!31 = !DILocation(line: 9, column: 9, scope: !27)
!32 = !DILocation(line: 10, column: 7, scope: !27)
!33 = !DILocation(line: 11, column: 7, scope: !27)
!34 = !DILocation(line: 12, column: 18, scope: !27)
!35 = !DILocation(line: 12, column: 20, scope: !27)
!36 = !DILocation(line: 12, column: 5, scope: !27)
!37 = !DILocation(line: 13, column: 18, scope: !27)
!38 = !DILocation(line: 13, column: 20, scope: !27)
!39 = !DILocation(line: 13, column: 5, scope: !27)
!40 = !DILocation(line: 14, column: 7, scope: !27)
!41 = !DILocation(line: 16, column: 9, scope: !42)
!42 = distinct !DILexicalBlock(scope: !27, file: !3, line: 16, column: 9)
!43 = !DILocation(line: 16, column: 9, scope: !27)
!44 = !DILocation(line: 18, column: 10, scope: !45)
!45 = distinct !DILexicalBlock(scope: !42, file: !3, line: 17, column: 5)
!46 = !DILocation(line: 18, column: 12, scope: !45)
!47 = !DILocation(line: 19, column: 11, scope: !45)
!48 = !DILocation(line: 20, column: 22, scope: !45)
!49 = !DILocation(line: 20, column: 24, scope: !45)
!50 = !DILocation(line: 20, column: 9, scope: !45)
!51 = !DILocation(line: 21, column: 22, scope: !45)
!52 = !DILocation(line: 21, column: 24, scope: !45)
!53 = !DILocation(line: 21, column: 9, scope: !45)
!54 = !DILocation(line: 22, column: 5, scope: !45)
!55 = !DILocation(line: 25, column: 10, scope: !56)
!56 = distinct !DILexicalBlock(scope: !42, file: !3, line: 24, column: 5)
!57 = !DILocation(line: 25, column: 12, scope: !56)
!58 = !DILocation(line: 26, column: 11, scope: !56)
!59 = !DILocation(line: 27, column: 22, scope: !56)
!60 = !DILocation(line: 27, column: 24, scope: !56)
!61 = !DILocation(line: 27, column: 9, scope: !56)
!62 = !DILocation(line: 28, column: 22, scope: !56)
!63 = !DILocation(line: 28, column: 24, scope: !56)
!64 = !DILocation(line: 28, column: 9, scope: !56)
!65 = !DILocation(line: 31, column: 17, scope: !27)
!66 = !DILocation(line: 31, column: 19, scope: !27)
!67 = !DILocation(line: 31, column: 5, scope: !27)
!68 = !DILocation(line: 32, column: 17, scope: !27)
!69 = !DILocation(line: 32, column: 19, scope: !27)
!70 = !DILocation(line: 32, column: 5, scope: !27)
!71 = !DILocation(line: 33, column: 17, scope: !27)
!72 = !DILocation(line: 33, column: 19, scope: !27)
!73 = !DILocation(line: 33, column: 5, scope: !27)
!74 = !DILocation(line: 34, column: 17, scope: !27)
!75 = !DILocation(line: 34, column: 19, scope: !27)
!76 = !DILocation(line: 34, column: 5, scope: !27)
!77 = !DILocation(line: 36, column: 9, scope: !27)
!78 = !DILocation(line: 36, column: 7, scope: !27)
!79 = !DILocation(line: 37, column: 17, scope: !27)
!80 = !DILocation(line: 37, column: 19, scope: !27)
!81 = !DILocation(line: 37, column: 5, scope: !27)
!82 = !DILocation(line: 38, column: 17, scope: !27)
!83 = !DILocation(line: 38, column: 19, scope: !27)
!84 = !DILocation(line: 38, column: 5, scope: !27)
!85 = !DILocation(line: 39, column: 17, scope: !27)
!86 = !DILocation(line: 39, column: 19, scope: !27)
!87 = !DILocation(line: 39, column: 5, scope: !27)
!88 = !DILocation(line: 40, column: 17, scope: !27)
!89 = !DILocation(line: 40, column: 19, scope: !27)
!90 = !DILocation(line: 40, column: 5, scope: !27)
!91 = !DILocation(line: 42, column: 9, scope: !27)
!92 = !DILocation(line: 42, column: 7, scope: !27)
!93 = !DILocation(line: 43, column: 7, scope: !27)
!94 = !DILocation(line: 43, column: 6, scope: !27)
!95 = !DILocation(line: 43, column: 9, scope: !27)
!96 = !DILocation(line: 44, column: 6, scope: !27)
!97 = !DILocation(line: 44, column: 8, scope: !27)
!98 = !DILocation(line: 45, column: 18, scope: !27)
!99 = !DILocation(line: 45, column: 5, scope: !27)
!100 = !DILocation(line: 46, column: 1, scope: !27)

; ModuleID = 'mytestcase.cpp'
source_filename = "mytestcase.cpp"
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
  br i1 %3, label %4, label %9, !dbg !36

4:                                                ; preds = %0
  store i32*** @a, i32**** @p, align 8, !dbg !37
  %5 = load i32***, i32**** @p, align 8, !dbg !39
  %6 = load i32**, i32*** @a, align 8, !dbg !40
  call void @_Z12MustPointsToIPPPiS1_EvT_T0_(i32*** %5, i32** %6), !dbg !41
  %7 = load i32***, i32**** @p, align 8, !dbg !42
  %8 = load i32**, i32*** @b, align 8, !dbg !43
  call void @_Z15DoesNotPointsToIPPPiS1_EvT_T0_(i32*** %7, i32** %8), !dbg !44
  br label %12, !dbg !45

9:                                                ; preds = %0
  store i32*** @b, i32**** @p, align 8, !dbg !46
  %10 = load i32***, i32**** @p, align 8, !dbg !48
  %11 = load i32**, i32*** @b, align 8, !dbg !49
  call void @_Z12MustPointsToIPPPiS1_EvT_T0_(i32*** %10, i32** %11), !dbg !50
  br label %12

12:                                               ; preds = %9, %4
  ret i32 0, !dbg !51
}

declare dso_local void @_Z12MustPointsToIPPPiS1_EvT_T0_(i32***, i32**) #1

declare dso_local void @_Z15DoesNotPointsToIPPPiS1_EvT_T0_(i32***, i32**) #1

attributes #0 = { noinline norecurse uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!24, !25, !26}
!llvm.ident = !{!27}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "p", scope: !2, file: !3, line: 2, type: !23, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "mytestcase.cpp", directory: "/home/mehul/Rnd_Project/testcases")
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
!31 = !DILocation(line: 4, column: 10, scope: !28)
!32 = !DILocation(line: 5, column: 14, scope: !28)
!33 = !DILocation(line: 5, column: 10, scope: !28)
!34 = !DILocation(line: 7, column: 12, scope: !35)
!35 = distinct !DILexicalBlock(scope: !28, file: !3, line: 7, column: 12)
!36 = !DILocation(line: 7, column: 12, scope: !28)
!37 = !DILocation(line: 8, column: 14, scope: !38)
!38 = distinct !DILexicalBlock(scope: !35, file: !3, line: 7, column: 15)
!39 = !DILocation(line: 10, column: 25, scope: !38)
!40 = !DILocation(line: 10, column: 28, scope: !38)
!41 = !DILocation(line: 10, column: 12, scope: !38)
!42 = !DILocation(line: 11, column: 28, scope: !38)
!43 = !DILocation(line: 11, column: 31, scope: !38)
!44 = !DILocation(line: 11, column: 12, scope: !38)
!45 = !DILocation(line: 12, column: 8, scope: !38)
!46 = !DILocation(line: 13, column: 14, scope: !47)
!47 = distinct !DILexicalBlock(scope: !35, file: !3, line: 12, column: 15)
!48 = !DILocation(line: 15, column: 25, scope: !47)
!49 = !DILocation(line: 15, column: 28, scope: !47)
!50 = !DILocation(line: 15, column: 12, scope: !47)
!51 = !DILocation(line: 18, column: 8, scope: !28)

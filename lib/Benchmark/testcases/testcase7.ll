; ModuleID = 'testcase7.cpp'
source_filename = "testcase7.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@p = dso_local global i32* null, align 8, !dbg !0
@q = dso_local global i32* null, align 8, !dbg !6
@x = dso_local global i32 0, align 4, !dbg !10
@y = dso_local global i32 0, align 4, !dbg !12

; Function Attrs: noinline nounwind uwtable
define dso_local void @_Z1gv() #0 !dbg !18 {
  %1 = load i32, i32* @y, align 4, !dbg !21
  %2 = icmp ne i32 %1, 0, !dbg !21
  br i1 %2, label %3, label %5, !dbg !23

3:                                                ; preds = %0
  store i32* @x, i32** @p, align 8, !dbg !24
  %4 = load i32*, i32** @q, align 8, !dbg !26
  store i32 20, i32* %4, align 4, !dbg !27
  br label %5, !dbg !28

5:                                                ; preds = %3, %0
  ret void, !dbg !29
}

; Function Attrs: noinline nounwind uwtable
define dso_local void @_Z1fv() #0 !dbg !30 {
  call void @_Z1gv(), !dbg !31
  %1 = load i32*, i32** @p, align 8, !dbg !32
  store i32 40, i32* %1, align 4, !dbg !33
  ret void, !dbg !34
}

; Function Attrs: noinline norecurse nounwind uwtable
define dso_local i32 @main() #1 !dbg !35 {
  store i32* @y, i32** @q, align 8, !dbg !38
  call void @_Z1fv(), !dbg !39
  %1 = load i32*, i32** @p, align 8, !dbg !40
  store i32 20, i32* %1, align 4, !dbg !41
  ret i32 0, !dbg !42
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline norecurse nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!14, !15, !16}
!llvm.ident = !{!17}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "p", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "testcase7.cpp", directory: "/home/mehul/Rnd_Project/testcases")
!4 = !{}
!5 = !{!0, !6, !10, !12}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "q", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!10 = !DIGlobalVariableExpression(var: !11, expr: !DIExpression())
!11 = distinct !DIGlobalVariable(name: "x", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!12 = !DIGlobalVariableExpression(var: !13, expr: !DIExpression())
!13 = distinct !DIGlobalVariable(name: "y", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!14 = !{i32 7, !"Dwarf Version", i32 4}
!15 = !{i32 2, !"Debug Info Version", i32 3}
!16 = !{i32 1, !"wchar_size", i32 4}
!17 = !{!"clang version 10.0.0-4ubuntu1 "}
!18 = distinct !DISubprogram(name: "g", linkageName: "_Z1gv", scope: !3, file: !3, line: 3, type: !19, scopeLine: 4, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!19 = !DISubroutineType(types: !20)
!20 = !{null}
!21 = !DILocation(line: 6, column: 9, scope: !22)
!22 = distinct !DILexicalBlock(scope: !18, file: !3, line: 6, column: 9)
!23 = !DILocation(line: 6, column: 9, scope: !18)
!24 = !DILocation(line: 8, column: 11, scope: !25)
!25 = distinct !DILexicalBlock(scope: !22, file: !3, line: 7, column: 5)
!26 = !DILocation(line: 9, column: 10, scope: !25)
!27 = !DILocation(line: 9, column: 12, scope: !25)
!28 = !DILocation(line: 10, column: 5, scope: !25)
!29 = !DILocation(line: 11, column: 1, scope: !18)
!30 = distinct !DISubprogram(name: "f", linkageName: "_Z1fv", scope: !3, file: !3, line: 12, type: !19, scopeLine: 13, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!31 = !DILocation(line: 14, column: 5, scope: !30)
!32 = !DILocation(line: 15, column: 6, scope: !30)
!33 = !DILocation(line: 15, column: 8, scope: !30)
!34 = !DILocation(line: 16, column: 1, scope: !30)
!35 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 18, type: !36, scopeLine: 19, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!36 = !DISubroutineType(types: !37)
!37 = !{!9}
!38 = !DILocation(line: 20, column: 7, scope: !35)
!39 = !DILocation(line: 21, column: 5, scope: !35)
!40 = !DILocation(line: 22, column: 6, scope: !35)
!41 = !DILocation(line: 22, column: 8, scope: !35)
!42 = !DILocation(line: 23, column: 1, scope: !35)

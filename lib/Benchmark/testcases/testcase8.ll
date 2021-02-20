; ModuleID = 'testcase8.cpp'
source_filename = "testcase8.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline norecurse nounwind uwtable
define dso_local i32 @main() #0 !dbg !7 {
  %1 = alloca i32, align 4
  %2 = alloca i32**, align 8
  %3 = alloca i32**, align 8
  %4 = alloca i32**, align 8
  %5 = alloca i32*, align 8
  %6 = alloca i32*, align 8
  %7 = alloca i32*, align 8
  %8 = alloca i32*, align 8
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32*** %2, metadata !11, metadata !DIExpression()), !dbg !14
  call void @llvm.dbg.declare(metadata i32*** %3, metadata !15, metadata !DIExpression()), !dbg !16
  call void @llvm.dbg.declare(metadata i32*** %4, metadata !17, metadata !DIExpression()), !dbg !18
  call void @llvm.dbg.declare(metadata i32** %5, metadata !19, metadata !DIExpression()), !dbg !20
  call void @llvm.dbg.declare(metadata i32** %6, metadata !21, metadata !DIExpression()), !dbg !22
  call void @llvm.dbg.declare(metadata i32** %7, metadata !23, metadata !DIExpression()), !dbg !24
  call void @llvm.dbg.declare(metadata i32** %8, metadata !25, metadata !DIExpression()), !dbg !26
  call void @llvm.dbg.declare(metadata i32* %9, metadata !27, metadata !DIExpression()), !dbg !28
  call void @llvm.dbg.declare(metadata i32* %10, metadata !29, metadata !DIExpression()), !dbg !30
  call void @llvm.dbg.declare(metadata i32* %11, metadata !31, metadata !DIExpression()), !dbg !32
  store i32** %5, i32*** %2, align 8, !dbg !33
  %12 = load i32*, i32** %5, align 8, !dbg !34
  store i32* %12, i32** %8, align 8, !dbg !35
  br label %13, !dbg !36

13:                                               ; preds = %33, %0
  %14 = load i32, i32* %9, align 4, !dbg !37
  %15 = icmp sgt i32 %14, 0, !dbg !38
  br i1 %15, label %16, label %37, !dbg !36

16:                                               ; preds = %13
  %17 = load i32**, i32*** %2, align 8, !dbg !39
  store i32* %10, i32** %17, align 8, !dbg !41
  br label %18, !dbg !42

18:                                               ; preds = %28, %16
  %19 = load i32, i32* %10, align 4, !dbg !43
  %20 = icmp sgt i32 %19, 0, !dbg !44
  br i1 %20, label %21, label %33, !dbg !42

21:                                               ; preds = %18
  store i32** %5, i32*** %2, align 8, !dbg !45
  store i32* %9, i32** %5, align 8, !dbg !47
  %22 = load i32, i32* %9, align 4, !dbg !48
  switch i32 %22, label %27 [
    i32 1, label %23
    i32 2, label %24
    i32 3, label %25
    i32 5, label %26
  ], !dbg !49

23:                                               ; preds = %21
  store i32* %10, i32** %5, align 8, !dbg !50
  br label %28, !dbg !52

24:                                               ; preds = %21
  store i32* %11, i32** %5, align 8, !dbg !53
  br label %28, !dbg !54

25:                                               ; preds = %21
  store i32* %9, i32** %6, align 8, !dbg !55
  br label %28, !dbg !56

26:                                               ; preds = %21
  br label %28, !dbg !57

27:                                               ; preds = %21
  store i32* %10, i32** %6, align 8, !dbg !58
  br label %28, !dbg !59

28:                                               ; preds = %27, %26, %25, %24, %23
  %29 = load i32*, i32** %8, align 8, !dbg !60
  %30 = load i32**, i32*** %2, align 8, !dbg !61
  store i32* %29, i32** %30, align 8, !dbg !62
  %31 = load i32, i32* %10, align 4, !dbg !63
  %32 = add nsw i32 %31, -1, !dbg !63
  store i32 %32, i32* %10, align 4, !dbg !63
  br label %18, !dbg !42, !llvm.loop !64

33:                                               ; preds = %18
  store i32** %6, i32*** %2, align 8, !dbg !66
  store i32** %5, i32*** %3, align 8, !dbg !67
  %34 = load i32**, i32*** %4, align 8, !dbg !68
  store i32** %34, i32*** %2, align 8, !dbg !69
  %35 = load i32, i32* %9, align 4, !dbg !70
  %36 = add nsw i32 %35, -1, !dbg !70
  store i32 %36, i32* %9, align 4, !dbg !70
  br label %13, !dbg !36, !llvm.loop !71

37:                                               ; preds = %13
  %38 = load i32, i32* %9, align 4, !dbg !73
  %39 = icmp sgt i32 %38, -1, !dbg !75
  br i1 %39, label %40, label %44, !dbg !76

40:                                               ; preds = %37
  %41 = load i32**, i32*** %3, align 8, !dbg !77
  %42 = load i32*, i32** %41, align 8, !dbg !79
  %43 = load i32**, i32*** %2, align 8, !dbg !80
  store i32* %42, i32** %43, align 8, !dbg !81
  br label %46, !dbg !82

44:                                               ; preds = %37
  %45 = load i32**, i32*** %3, align 8, !dbg !83
  store i32* %9, i32** %45, align 8, !dbg !85
  br label %46

46:                                               ; preds = %44, %40
  store i32* %9, i32** %5, align 8, !dbg !86
  store i32* %10, i32** %6, align 8, !dbg !87
  ret i32 0, !dbg !88
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline norecurse nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5}
!llvm.ident = !{!6}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !1, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "testcase8.cpp", directory: "/home/mehul/Rnd_Project/testcases")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{!"clang version 10.0.0-4ubuntu1 "}
!7 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 4, type: !8, scopeLine: 4, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!8 = !DISubroutineType(types: !9)
!9 = !{!10}
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !DILocalVariable(name: "p", scope: !7, file: !1, line: 5, type: !12)
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64)
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!14 = !DILocation(line: 5, column: 11, scope: !7)
!15 = !DILocalVariable(name: "q", scope: !7, file: !1, line: 5, type: !12)
!16 = !DILocation(line: 5, column: 16, scope: !7)
!17 = !DILocalVariable(name: "r", scope: !7, file: !1, line: 5, type: !12)
!18 = !DILocation(line: 5, column: 21, scope: !7)
!19 = !DILocalVariable(name: "x", scope: !7, file: !1, line: 5, type: !13)
!20 = !DILocation(line: 5, column: 25, scope: !7)
!21 = !DILocalVariable(name: "y", scope: !7, file: !1, line: 5, type: !13)
!22 = !DILocation(line: 5, column: 29, scope: !7)
!23 = !DILocalVariable(name: "z", scope: !7, file: !1, line: 5, type: !13)
!24 = !DILocation(line: 5, column: 33, scope: !7)
!25 = !DILocalVariable(name: "w", scope: !7, file: !1, line: 5, type: !13)
!26 = !DILocation(line: 5, column: 38, scope: !7)
!27 = !DILocalVariable(name: "a", scope: !7, file: !1, line: 5, type: !10)
!28 = !DILocation(line: 5, column: 41, scope: !7)
!29 = !DILocalVariable(name: "b", scope: !7, file: !1, line: 5, type: !10)
!30 = !DILocation(line: 5, column: 44, scope: !7)
!31 = !DILocalVariable(name: "c", scope: !7, file: !1, line: 5, type: !10)
!32 = !DILocation(line: 5, column: 47, scope: !7)
!33 = !DILocation(line: 6, column: 7, scope: !7)
!34 = !DILocation(line: 7, column: 9, scope: !7)
!35 = !DILocation(line: 7, column: 7, scope: !7)
!36 = !DILocation(line: 8, column: 5, scope: !7)
!37 = !DILocation(line: 8, column: 11, scope: !7)
!38 = !DILocation(line: 8, column: 13, scope: !7)
!39 = !DILocation(line: 9, column: 10, scope: !40)
!40 = distinct !DILexicalBlock(scope: !7, file: !1, line: 8, column: 17)
!41 = !DILocation(line: 9, column: 12, scope: !40)
!42 = !DILocation(line: 10, column: 9, scope: !40)
!43 = !DILocation(line: 10, column: 15, scope: !40)
!44 = !DILocation(line: 10, column: 17, scope: !40)
!45 = !DILocation(line: 11, column: 15, scope: !46)
!46 = distinct !DILexicalBlock(scope: !40, file: !1, line: 10, column: 21)
!47 = !DILocation(line: 12, column: 15, scope: !46)
!48 = !DILocation(line: 13, column: 20, scope: !46)
!49 = !DILocation(line: 13, column: 13, scope: !46)
!50 = !DILocation(line: 15, column: 23, scope: !51)
!51 = distinct !DILexicalBlock(scope: !46, file: !1, line: 13, column: 22)
!52 = !DILocation(line: 16, column: 21, scope: !51)
!53 = !DILocation(line: 18, column: 23, scope: !51)
!54 = !DILocation(line: 19, column: 21, scope: !51)
!55 = !DILocation(line: 21, column: 23, scope: !51)
!56 = !DILocation(line: 22, column: 21, scope: !51)
!57 = !DILocation(line: 24, column: 21, scope: !51)
!58 = !DILocation(line: 26, column: 23, scope: !51)
!59 = !DILocation(line: 27, column: 21, scope: !51)
!60 = !DILocation(line: 29, column: 18, scope: !46)
!61 = !DILocation(line: 29, column: 14, scope: !46)
!62 = !DILocation(line: 29, column: 16, scope: !46)
!63 = !DILocation(line: 30, column: 14, scope: !46)
!64 = distinct !{!64, !42, !65}
!65 = !DILocation(line: 31, column: 9, scope: !40)
!66 = !DILocation(line: 32, column: 11, scope: !40)
!67 = !DILocation(line: 33, column: 11, scope: !40)
!68 = !DILocation(line: 34, column: 13, scope: !40)
!69 = !DILocation(line: 34, column: 11, scope: !40)
!70 = !DILocation(line: 35, column: 10, scope: !40)
!71 = distinct !{!71, !36, !72}
!72 = !DILocation(line: 36, column: 5, scope: !7)
!73 = !DILocation(line: 37, column: 8, scope: !74)
!74 = distinct !DILexicalBlock(scope: !7, file: !1, line: 37, column: 8)
!75 = !DILocation(line: 37, column: 10, scope: !74)
!76 = !DILocation(line: 37, column: 8, scope: !7)
!77 = !DILocation(line: 38, column: 15, scope: !78)
!78 = distinct !DILexicalBlock(scope: !74, file: !1, line: 37, column: 15)
!79 = !DILocation(line: 38, column: 14, scope: !78)
!80 = !DILocation(line: 38, column: 10, scope: !78)
!81 = !DILocation(line: 38, column: 12, scope: !78)
!82 = !DILocation(line: 39, column: 5, scope: !78)
!83 = !DILocation(line: 41, column: 10, scope: !84)
!84 = distinct !DILexicalBlock(scope: !74, file: !1, line: 40, column: 9)
!85 = !DILocation(line: 41, column: 12, scope: !84)
!86 = !DILocation(line: 43, column: 7, scope: !7)
!87 = !DILocation(line: 44, column: 7, scope: !7)
!88 = !DILocation(line: 45, column: 5, scope: !7)

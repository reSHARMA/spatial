; ModuleID = 'errtc1.cpp'
source_filename = "errtc1.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline norecurse uwtable
define dso_local i32 @main() #0 !dbg !7 {
  %1 = alloca i32, align 4
  %2 = alloca i32**, align 8
  %3 = alloca i32**, align 8
  %4 = alloca i32**, align 8
  %5 = alloca i32*, align 8
  %6 = alloca i32*, align 8
  %7 = alloca i32*, align 8
  %8 = alloca i32*, align 8
  %9 = alloca i32*, align 8
  %10 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32*** %2, metadata !11, metadata !DIExpression()), !dbg !14
  call void @llvm.dbg.declare(metadata i32*** %3, metadata !15, metadata !DIExpression()), !dbg !16
  call void @llvm.dbg.declare(metadata i32*** %4, metadata !17, metadata !DIExpression()), !dbg !18
  call void @llvm.dbg.declare(metadata i32** %5, metadata !19, metadata !DIExpression()), !dbg !20
  call void @llvm.dbg.declare(metadata i32** %6, metadata !21, metadata !DIExpression()), !dbg !22
  call void @llvm.dbg.declare(metadata i32** %7, metadata !23, metadata !DIExpression()), !dbg !24
  call void @llvm.dbg.declare(metadata i32** %8, metadata !25, metadata !DIExpression()), !dbg !26
  call void @llvm.dbg.declare(metadata i32** %9, metadata !27, metadata !DIExpression()), !dbg !28
  call void @llvm.dbg.declare(metadata i32* %10, metadata !29, metadata !DIExpression()), !dbg !30
  br label %11, !dbg !31

11:                                               ; preds = %21, %0
  %12 = load i32**, i32*** %3, align 8, !dbg !32
  store i32* %10, i32** %12, align 8, !dbg !34
  %13 = load i32*, i32** %6, align 8, !dbg !35
  %14 = load i32, i32* %10, align 4, !dbg !36
  call void @_Z11MayPointsToIPiiEvT_T0_(i32* %13, i32 %14), !dbg !37
  %15 = load i32, i32* %10, align 4, !dbg !38
  %16 = icmp ne i32 %15, 0, !dbg !38
  br i1 %16, label %17, label %18, !dbg !40

17:                                               ; preds = %11
  store i32** %6, i32*** %3, align 8, !dbg !41
  br label %18, !dbg !43

18:                                               ; preds = %17, %11
  %19 = load i32**, i32*** %3, align 8, !dbg !44
  %20 = load i32*, i32** %6, align 8, !dbg !45
  call void @_Z11MayPointsToIPPiS0_EvT_T0_(i32** %19, i32* %20), !dbg !46
  br label %21, !dbg !47

21:                                               ; preds = %18
  br i1 true, label %11, label %22, !dbg !47, !llvm.loop !48

22:                                               ; preds = %21
  store i32** %9, i32*** %3, align 8, !dbg !50
  %23 = load i32, i32* %1, align 4, !dbg !51
  ret i32 %23, !dbg !51
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local void @_Z11MayPointsToIPiiEvT_T0_(i32*, i32) #2

declare dso_local void @_Z11MayPointsToIPPiS0_EvT_T0_(i32**, i32*) #2

attributes #0 = { noinline norecurse uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5}
!llvm.ident = !{!6}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !1, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "errtc1.cpp", directory: "/home/mehul/Rnd_Project/testcases")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{!"clang version 10.0.0-4ubuntu1 "}
!7 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 3, type: !8, scopeLine: 4, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
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
!19 = !DILocalVariable(name: "a", scope: !7, file: !1, line: 6, type: !13)
!20 = !DILocation(line: 6, column: 10, scope: !7)
!21 = !DILocalVariable(name: "b", scope: !7, file: !1, line: 6, type: !13)
!22 = !DILocation(line: 6, column: 14, scope: !7)
!23 = !DILocalVariable(name: "c", scope: !7, file: !1, line: 6, type: !13)
!24 = !DILocation(line: 6, column: 18, scope: !7)
!25 = !DILocalVariable(name: "d", scope: !7, file: !1, line: 6, type: !13)
!26 = !DILocation(line: 6, column: 22, scope: !7)
!27 = !DILocalVariable(name: "e", scope: !7, file: !1, line: 6, type: !13)
!28 = !DILocation(line: 6, column: 26, scope: !7)
!29 = !DILocalVariable(name: "m", scope: !7, file: !1, line: 7, type: !10)
!30 = !DILocation(line: 7, column: 9, scope: !7)
!31 = !DILocation(line: 8, column: 5, scope: !7)
!32 = !DILocation(line: 10, column: 10, scope: !33)
!33 = distinct !DILexicalBlock(scope: !7, file: !1, line: 9, column: 5)
!34 = !DILocation(line: 10, column: 12, scope: !33)
!35 = !DILocation(line: 11, column: 21, scope: !33)
!36 = !DILocation(line: 11, column: 23, scope: !33)
!37 = !DILocation(line: 11, column: 9, scope: !33)
!38 = !DILocation(line: 12, column: 13, scope: !39)
!39 = distinct !DILexicalBlock(scope: !33, file: !1, line: 12, column: 13)
!40 = !DILocation(line: 12, column: 13, scope: !33)
!41 = !DILocation(line: 14, column: 15, scope: !42)
!42 = distinct !DILexicalBlock(scope: !39, file: !1, line: 13, column: 9)
!43 = !DILocation(line: 15, column: 9, scope: !42)
!44 = !DILocation(line: 16, column: 21, scope: !33)
!45 = !DILocation(line: 16, column: 23, scope: !33)
!46 = !DILocation(line: 16, column: 9, scope: !33)
!47 = !DILocation(line: 17, column: 5, scope: !33)
!48 = distinct !{!48, !31, !49}
!49 = !DILocation(line: 17, column: 15, scope: !7)
!50 = !DILocation(line: 18, column: 7, scope: !7)
!51 = !DILocation(line: 19, column: 1, scope: !7)
